#version 450

layout(location = 0) in vec2 uv;

layout(location = 0) out vec4 out_color;

// Raymarching constants
const int MAX_STEPS = 64;
const float MIN_HIT_DISTANCE = 0.001;
const float MAX_TRACE_DISTANCE = 1000.0;

// Variables
vec3 camera_pos = vec3(0.0, 0.0, -2.0);
vec3 light_pos = vec3(2.0, 5.0, 3.0);

// Signed distance functions
// - Sphere
float sdf_sphere(vec3 p, vec3 c, float r) {
    return length(p - c) - r;
}
// - Cube
float sdf_cube(vec3 p) {
    return 0.0;
}

// Scene
float scene(vec3 p) {
    float sphere_0 = sdf_sphere(p, vec3(0.0, 0.0, 0.0), 1.0);
    
    return sphere_0;
}

// Calculate normals
vec3 normal(vec3 p) {
    const vec3 small_step = vec3(0.001, 0.0, 0.0);

    float gradient_x = scene(p + small_step.xyy) - scene(p - small_step.xyy);
    float gradient_y = scene(p + small_step.yxy) - scene(p - small_step.yxy);
    float gradient_z = scene(p + small_step.yyx) - scene(p - small_step.yyx);

    vec3 n = vec3(gradient_x, gradient_y, gradient_z);
    
    return normalize(n);
}

// Ray marching algorithm
float ray_march(vec3 ray_origin, vec3 ray_dir) {
    float trace_distance = 0.0;
    
    for (int i = 0; i < MAX_STEPS; i++) {
        vec3 current_pos = ray_origin + trace_distance * ray_dir;
        float closest_distance = scene(current_pos);
        
        if (closest_distance < MIN_HIT_DISTANCE) { // Hit!
            return trace_distance;
        }
        
        if (trace_distance > MAX_TRACE_DISTANCE)
            break;
        
        trace_distance += closest_distance;
    }
    
    return -1.0; // Miss
}

// Draw
vec3 render(vec3 ray_origin, vec3 ray_dir) {
    vec3 color;
    float ray = ray_march(ray_origin, ray_dir);
    
    if (ray == -1.0) { // Sky
        color = vec3(0.4, 0.4, 0.8) - (ray_dir.y * 0.2);
    } else {
        vec3 object_color = vec3(0.5, 0.9, 0.4);
        vec3 ambient = vec3(0.1);
        
        vec3 current_pos = ray_origin + ray * ray_dir;
        vec3 light_dir = normalize(current_pos - light_pos);
        
        vec3 directional_light = max(0.0, dot(normal(current_pos), light_dir)) * vec3(0.9);
        vec3 ambient_light = vec3(0.1);
        color = object_color * (directional_light + ambient_light);
    }
    
    return color;
}

void main() {
    vec3 ro = camera_pos;
    vec3 rd = vec3(uv, 1.0);
    
    out_color = vec4(render(ro, rd), 1.0);
}

/*
 
 
 float diffuse_intensity = max(0.0, dot(normal(current_pos), light_dir));
 return vec3(1.0) * diffuse_intensity;
 */
