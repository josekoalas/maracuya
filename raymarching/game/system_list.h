//project verse, 2017-2022
//by jose pazos perez

#pragma once

#include "scene.h"

#include "log.h"
#include "input.h"
#include "r_graphics.h"
#include "f_time.h"

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
                Graphics::camera.proj_type = Graphics::PROJECTION_NONE;
                Graphics::updateCameraProjection(Graphics::camera);
                Graphics::camera.pos = glm::vec3(0.0f);
                init = true;
            }
            
            UniformBuffer buffer{};
            buffer.time = sec(time() - start_time);
            
            for (auto &uniforms : Graphics::api.pipelines.at("test").uniform_buffers)
                for (auto &u : uniforms)
                    Graphics::API::updateUniformBuffer(Graphics::api, u, buffer);
        }
    };
}
