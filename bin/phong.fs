#version 150

uniform vec3 EyePos = vec3(4, 4, 4);
uniform vec3 SurfaceDiffuse;
uniform vec3 SurfaceSpecular;
uniform float SurfaceSmooth;
uniform vec3 LightPos[2] = vec3[2](vec3(-2, 10, 10), vec3(5, 5, -7));
uniform vec3 LightIntensity[2] = vec3[2](vec3(0.6f, 2.f, 2.f), vec3(1.6f, 1.0f, 0.2f));

in vec3 WorldPos;
in vec3 WorldNormal;
in vec3 normal;

out vec4 Color;

vec3 Shade(vec3 p, vec3 n) {
	vec3 Lo = vec3 ( .25f, .15f, .15f );
	
    vec3 eyeVec = normalize(EyePos - p);
    vec3 lightVec = normalize(LightPos[0] - p);
    vec3 halfVec = 0.5 * (eyeVec + lightVec);
    float cosTh = clamp(dot(n, halfVec), 0, 1);
    float cosTi = clamp(dot(n, lightVec), 0, 1);
    Lo += (SurfaceDiffuse + SurfaceSpecular * pow(cosTh, SurfaceSmooth)) * LightIntensity[0] * cosTi;
    
    
    lightVec = normalize(LightPos[1] - p);
    halfVec = 0.5 * (eyeVec + lightVec);
    cosTh = clamp(dot(n, halfVec), 0, 1);
    cosTi = clamp(dot(n, lightVec), 0, 1);
    Lo += (SurfaceDiffuse + SurfaceSpecular * pow(cosTh, SurfaceSmooth)) * LightIntensity[1] * cosTi;

    return Lo;
}

void main() {
    vec3 nw = normalize(WorldNormal);
    Color.rgb = Shade(WorldPos, nw);
    Color.a = 1;
}
