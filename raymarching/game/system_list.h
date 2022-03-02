//project verse, 2017-2022
//by jose pazos perez

#pragma once

#include "scene.h"

#include "log.h"
#include "input.h"
#include "r_graphics.h"
#include "f_time.h"

using namespace Fresa::Graphics;

namespace Fresa::System
{
    struct UniformBuffer {
        float time;
    };
    
    inline Clock::time_point start_time = time();
    
    struct SomeSystem : PhysicsUpdate<SomeSystem, PRIORITY_MOVEMENT>, RenderUpdate<SomeSystem> {
        inline static void update() { }
        
        inline static void render() {
            static bool init = false;
            if (not init) {
                camera.proj_type = PROJECTION_NONE;
                updateCameraProjection(camera);
                camera.pos = glm::vec3(0.0f);
                init = true;
            }
            
            UniformBuffer buffer{};
            buffer.time = sec(time() - start_time);
            
            #if defined USE_VULKAN
            for (auto &uniforms : api.pipelines.at("test").uniform_buffers)
                for (auto &u : uniforms)
                    API::updateUniformBuffer(api, u, buffer);
            #elif defined USE_OPENGL
            for (auto &[key, u] : API::shaders.at("test").uniforms)
                API::updateUniformBuffer(api, BufferData{u}, buffer);
            #endif
        }
    };
}
