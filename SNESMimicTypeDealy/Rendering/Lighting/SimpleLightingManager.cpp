#include "SimpleLightingManager.h"
#include "../Renderers/Renderer.h"

#include <algorithm>

namespace GAME_NAME::Rendering::Lighting
{

	int SimpleLightingManager::m_vertexExecutionID = -1;
	std::vector<std::vector<LightingSource*>> SimpleLightingManager::m_sources;
	std::vector<LightingSource*> SimpleLightingManager::m_dynamicSources;
	
	void SimpleLightingManager::EnableLighting(int lightingGroups, bool allowBackgroundLighting)
	{
		//If lighting is already enabled, just reset everything.
		if (m_sources.size() > 0 || m_dynamicSources.size() > 0)
		{
			DisableLighting();
		}

		if (m_vertexExecutionID < 0)
		{
			m_vertexExecutionID = Sprite::AddPrerenderExecution(lightingExecution);
		}

		for (int x = 0; x < lightingGroups; x++)
		{
			m_sources.push_back(std::vector<LightingSource*>(10));
		}

		m_backgroundLighting = allowBackgroundLighting;
	}

	void SimpleLightingManager::DisableLighting()
	{
		//Remove prerender execution.

		for (int i = 0; i < m_sources.size(); i++)
		{
			for (LightingSource*& source : m_sources[i])
			{
				delete source;
			}

			m_sources[i].clear();
		}
		m_sources.clear();

		for (LightingSource*& source : m_dynamicSources)
		{
			delete source;
		}
		m_dynamicSources.clear();
		
		m_vertexExecutionID = -1;
	}

	void SimpleLightingManager::RegisterSource(LightingSource* source, bool dynamic)
	{
		//Lighting is not turned on.
		if (m_vertexExecutionID < 0) { return; }

		if (dynamic)
		{
			m_dynamicSources.push_back(source);
			return;
		}

		m_sources[getLightingGroupID(source->GetPosition().X)].push_back(source);
	}

	void SimpleLightingManager::RemoveSource(LightingSource* source, bool dynamic)
	{
		//Lighting is not turned on.
		if (m_vertexExecutionID < 0) { return; }

		if (dynamic)
		{
			auto result = std::find(m_dynamicSources.begin(), m_dynamicSources.end(), source);

			if (result != m_dynamicSources.end())
			{
				m_dynamicSources.erase(result);
			}

			return;
		}

		std::vector<LightingSource*>& arr = m_sources[getLightingGroupID(source->GetPosition().X)];

		auto result = std::find(arr.begin(), arr.end(), source);

		if (result != arr.end())
		{
			arr.erase(result);
		}
	}

	void ApplyLightingEffect(LightingSource* source, VertexData* data, const Vec2& vertexPosition/*, std::mutex* dataMutex*/)
	{
		float distance = Vec2::Distance(source->GetPosition(), vertexPosition);
		float appliedPower = (source->GetPower() - distance) / (source->GetPower() - source->GetFalloff());


		if (appliedPower > 0.f)
		{
			//dataMutex->lock();
			//Update color so that this effect can apply over top of other effects.
			data->Color = Vec4(data->Color.X + appliedPower, data->Color.Y + appliedPower, data->Color.Z + appliedPower, 1.f);
			//dataMutex->unlock();
		}
	}

	void SimpleLightingManager::lightingExecution(Sprite* sprite, const Vec2& worldPosition, const Vec2& scale, const float& rotation, VertexData* data)
	{
		
		if (m_backgroundLighting || Renderer::CurrentlyRenderingLayer == RENDER_LAYER_OBJECTS || Renderer::CurrentlyRenderingLayer == RENDER_LAYER_OBJECTS_FRONT || Renderer::CurrentlyRenderingLayer == RENDER_LAYER_ACTIVE_OBJECTS)
		{
			//If the color was not changed, make the object have no light.
			data->SetColor(Vec4(0.f, 0.f, 0.f, 1.f));

			const Vec2 vertexPosition = (data->Position * scale) + worldPosition;

			//std::mutex* dataMutex = new std::mutex();
			
			const int group = getLightingGroupID(worldPosition.X);

			for (LightingSource* source : m_dynamicSources)
			{
				if (source == nullptr) { continue; }
				ApplyLightingEffect(source, data, vertexPosition);
			}

			for (LightingSource* source : m_sources[group])
			{
				if (source == nullptr) { continue; }
				ApplyLightingEffect(source, data, vertexPosition);
			}

			if (group > 0)
			{
				for (LightingSource* source : m_sources[group - 1])
				{
					if (source == nullptr) { continue; }
					ApplyLightingEffect(source, data, vertexPosition);
				}
			}

			if (group < m_sources.size() - 1)
			{
				for (LightingSource* source : m_sources[group + 1])
				{
					if (source == nullptr) { continue; }
					ApplyLightingEffect(source, data, vertexPosition);
				}
			}

			/*
				THREADING GOOFY because this function is not always in the main thread. Sometimes it is called from other threads.
			*/

			/*std::thread mainGroup([group, data, vertexPosition](std::mutex* dataMutex) {
				for (LightingSource* source : m_sources[group])
				{
					if (source == nullptr) { continue; }
					ApplyLightingEffect(source, data, vertexPosition, dataMutex);
				}
			}, dataMutex);

			//Check for lights in nearby groups too.
			std::thread backGroup([group, data, vertexPosition](std::mutex* dataMutex) {
				if (group > 0)
				{
					for (LightingSource* source : m_sources[group - 1])
					{
						if (source == nullptr) { continue; }
						ApplyLightingEffect(source, data, vertexPosition, dataMutex);
					}
				}
			}, dataMutex);

			std::thread frontGroup([group, data, vertexPosition](std::mutex* dataMutex) {
				if (group < m_sources.size() - 1)
				{
					for (LightingSource* source : m_sources[group + 1])
					{
						if (source == nullptr) { continue; }
						ApplyLightingEffect(source, data, vertexPosition, dataMutex);
					}
				}
			}, dataMutex);

			mainGroup.join();
			backGroup.join();
			frontGroup.join();*/

			//delete dataMutex;
		}
	}

}