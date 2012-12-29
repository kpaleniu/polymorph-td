#include "game/Entity.hpp"
#include "game/World.hpp"

#include "gr/TestWindow.hpp"
#include <gr/RenderPass.hpp>
#include <gr/opengl.hpp>
#include <gr/BufferManager.hpp>
#include <gr/types.hpp>
#include <gr/Surface.hpp>

#include <text/util.hpp>
#include <Debug.hpp>

#include <windows.h>

namespace
{
	const char* TAG = "GameTest";

	text::string_hash testEnt1 = text::intern("TestEntity1");
	text::string_hash pos = text::intern("pos");
}

class EntityVS : public gr::VertexSupplier
{
public:
	EntityVS(const game::EntityManager::EntityReadView& entity)
	:	_pos(entity.findReader(pos)) {}

	void writeVertices(gr::VertexWriter& writer)
	{
		writer.vertices() << std::vector<gr::real_t>
		{
			{
				_pos.read(0).asFloat() - 0.5f,
				_pos.read(1).asFloat() - 0.5f,

				_pos.read(0).asFloat() + 0.5f,
				_pos.read(1).asFloat() - 0.5f,

				_pos.read(0).asFloat() + 0.5f,
				_pos.read(1).asFloat() + 0.5f,

				_pos.read(0).asFloat() - 0.5f,
				_pos.read(1).asFloat() + 0.5f
			}
		};

		writer.indices() << std::vector<gr::index_t>{{0, 1, 2, 3}};
	}

private:
	const game::Component::Reader _pos;

};

/**
 * Windows main.
 */
int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE, LPSTR, int)
{
	DEBUG_OUT(TAG, "Starting test");

	createTestWindow(hInstance);

	try
	{
		auto surface = createSurface();

		game::World world;

		gr::BufferManager bufferManager;


		gr::RenderPass::BufferDesc bufferDesc;
		bufferDesc.clearFlags = gr::enum_t(gr::BufferFlag::COLOR);
		bufferDesc.useFlags = gr::enum_t(gr::BufferFlag::COLOR);

		gr::RenderPass::MaterialDesc materialDesc;
		materialDesc.shader = nullptr;
		materialDesc.texture = nullptr;

		gr::RenderPass::TransformDesc transformDesc =
		{
			gr::Projection::ortho(-1, 1, -1, 1, 1, -1),
			gr::Transform::identity(),
			gr::Transform::identity()
		};


		gr::RenderPass pass(bufferManager,
		                    gr::VertexFormat::V2,
		                    gr::Primitive::QUADS,
		                    materialDesc,
		                    bufferDesc,
		                    transformDesc);

		{
			auto entityView = world.entityManager().addEntity(testEnt1);
			auto componentWriter = entityView.addComponent(pos);
			componentWriter.insert(0.0f).insert(0.0f).insert(0.0f);
			world.entityManager().flipBuffers();
		}

		auto entity = world.entityManager().findEntity(testEnt1);
		auto vs = EntityVS(entity);
		pass.addVertexSupplier(vs);
		pass.preRender(
		[&]
		{ world.entityManager().flipMutex().lock(); });

		pass.postRender(
		[&]
		{ world.entityManager().flipMutex().unlock(); });

		auto posWriter = entity.findWriter(pos);
		auto posReader = entity.findReader(pos);

		float dir = 1.0f;

		while (updateTestWindow())
		{
			pass.render();

			float x = posReader.read(0).asFloat();

			if (x > 1.0f)
				dir = -1.0f;
			else if (x < -1.0f)
				dir = 1.0f;

			x += dir * 0.001f;

			posWriter.write(x, 0);
			world.entityManager().flipBuffers();

			surface.flipBuffers();
		}


	}
	catch (std::exception& e)
	{
		DEBUG_OUT(TAG, e.what());
	}
	catch (...)
	{
		DEBUG_OUT(TAG, "Error");
	}

	destroyTestWindow();

	DEBUG_OUT(TAG, "Closing");

	return 0;
}
