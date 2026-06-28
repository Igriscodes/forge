#version 330 core
out vec4 FragColor;
in vec2 TexCoords;
uniform float u_time;
uniform vec2 u_resolution;
#define MAX_STEPS 100
#define MAX_DIST 100.0
#define SURF_DIST 0.001
mat2 rot(float a) {
    float s = sin(a), c = cos(a);
    return mat2(c, -s, s, c);
}
float sdBox( vec3 p, vec3 b ) {
  vec3 q = abs(p) - b;
  return length(max(q,0.0)) + min(max(q.x,max(q.y,q.z)),0.0);
}
float map(vec3 p) {
    vec3 q = p;
    q.xz = mod(p.xz + 4.0, 8.0) - 4.0;
    float ground = p.y + 2.0;
    float core = sdBox(q, vec3(1.5, 5.0, 1.5));
    vec3 q2 = q;
    q2.y = mod(q2.y, 1.0) - 0.5;
    float cuts = sdBox(q2, vec3(2.0, 0.1, 2.0));
    float structure = max(core, -cuts);
    vec3 p_pipes = p;
    p_pipes.y -= 1.0;
    p_pipes.z = mod(p_pipes.z + 1.0, 2.0) - 1.0;
    float pipes = length(p_pipes.yz) - 0.2;
    float scene = min(ground, structure);
    scene = min(scene, pipes);
    return scene;
}
vec3 getNormal(vec3 p) {
    float d = map(p);
    vec2 e = vec2(0.001, 0);
    vec3 n = d - vec3(map(p - e.xyy), map(p - e.yxy), map(p - e.yyx));
    return normalize(n);
}
float rayMarch(vec3 ro, vec3 rd) {
    float dO = 0.0;
    for(int i = 0; i < MAX_STEPS; i++) {
        vec3 p = ro + rd * dO;
        float dS = map(p);
        dO += dS;
        if(dO > MAX_DIST || abs(dS) < SURF_DIST) break;
    }
    return dO;
}
void main() {
    vec2 uv = (TexCoords - 0.5) * 2.0;
    uv.x *= u_resolution.x / u_resolution.y;
    vec3 ro = vec3(u_time * 2.0, 2.0, u_time * 3.0);
    vec3 lookAt = ro + vec3(sin(u_time * 0.2), -0.2, cos(u_time * 0.2));
    vec3 f = normalize(lookAt - ro);
    vec3 r = normalize(cross(vec3(0,1,0), f));
    vec3 u = cross(f, r);
    vec3 rd = normalize(f + uv.x * r + uv.y * u);
    float d = rayMarch(ro, rd);
    vec3 col = vec3(0.0);
    if(d < MAX_DIST) {
        vec3 p = ro + rd * d;
        vec3 n = getNormal(p);
        vec3 lightPos = ro + vec3(0.0, 5.0, 0.0);
        vec3 l = normalize(lightPos - p);
        float dif = clamp(dot(n, l), 0.0, 1.0);
        vec3 heatColor = mix(vec3(1.0, 0.2, 0.0), vec3(0.0, 0.5, 1.0), p.y * 0.2);
        float fog = exp(-d * 0.03);
        col = vec3(dif) * 0.2 + heatColor * (1.0 - fog) + vec3(0.1) * max(0.0, dot(n, vec3(0,1,0)));
        col = mix(vec3(0.05, 0.05, 0.1), col, fog);
    } else {
        col = vec3(0.05, 0.05, 0.1);
    }
    col = col * 1.5;
    col = pow(col, vec3(1.0/2.2));
    FragColor = vec4(col, 1.0);
}
