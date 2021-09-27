#version 410 core

layout (location = 0) in vec3 VertexPosition;
layout (location = 1) in vec3 VertexNormal;

out vec3 LightIntensity;
out vec3 vPosition;
out vec3 vNormal;
out mat4 ModelViewMatrix_Frag;
out mat3 NormalMatrix_Frag;

layout (std140) uniform LightInfo {
    vec4 Position;// Light Position in eye coord.
    vec3 La;// Ambient light intensity
    vec3 Ld;// Diffuse light intensity
    vec3 Ls;// Specular light intensity
} light;

layout(std140) uniform MaterialInfo {
    vec3 Ka;// Ambient reflectivity
    vec3 Kd;// Diffuse reflectivity
    vec3 Ks;// Specular reflectivity
    float Shininess;// Specular shininess factor
} material;

layout(std140) uniform VertInfo {
    mat4 ModelViewMatrix;
    mat3 NormalMatrix;
    mat4 ProjectionMatrix;
    mat4 MVP;
} vert;

subroutine vec3 processLighting(vec3 pos, vec3 norm);
subroutine uniform processLighting lightProcessor;
subroutine(processLighting)
vec3 gouradPhongModel(vec3 pos, vec3 norm) {
    vec3 n = normalize( vert.NormalMatrix * norm );
    vec4 camCoords = vert.ModelViewMatrix * vec4(pos,1.0);
    vec3 ambient = light.La * material.Ka;
    vec3 s = normalize(vec3(light.Position - camCoords));
    float sDotN = max( dot(s,n), 0.0);
    vec3 diffuse = light.Ld * material.Kd * sDotN;
    vec3 specular = vec3(0.0);
    if (sDotN > 0.0) {
        vec3 v = normalize(-camCoords.xyz);
        vec3 r = reflect( -s, n);
        specular = light.Ls * material.Ks * pow( max( dot(r,v), 0.0), material.Shininess);
    }
    return ambient + diffuse + specular;
}
subroutine (processLighting)
vec3 gouradBlinnPhong(vec3 pos, vec3 norm) {
    vec3 ambient = light.La * material.Ka;
    vec3 s = normalize( light.Position.xyz - pos );
    float sDotN = max( dot(s,norm), 0.0);
    vec3 diffuse = light.Ld * material.Kd * sDotN;
    vec3 specular = vec3(0.0);
    if (sDotN > 0.0) {
        vec3 v = normalize(-pos.xyz);
        vec3 h = normalize( v + s);
        specular = light.Ls * material.Ks * pow( max( dot(h,norm), 0.0), material.Shininess);
    }
    return ambient + diffuse + specular;
}
subroutine (processLighting)
vec3 phongPassThrough(vec3 pos, vec3 norm) {
    return vec3(0,0,0);
}

void main() {
    LightIntensity = lightProcessor(VertexPosition, VertexNormal);

    vNormal = normalize(vert.NormalMatrix * VertexNormal);
    vPosition = ( vert.ModelViewMatrix * vec4(VertexPosition, 1.0)).xyz;
    ModelViewMatrix_Frag = vert.ModelViewMatrix;
    NormalMatrix_Frag = vert.NormalMatrix;
    gl_Position = vert.MVP * vec4(VertexPosition,1.0);
}