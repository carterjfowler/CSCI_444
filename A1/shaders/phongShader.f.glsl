#version 410 core

in vec3 vPosition;
in vec3 vNormal;
in mat4 ModelViewMatrix_Frag;
in mat3 NormalMatrix_Frag;

//Uniforms
uniform LightInfo {
    vec4 Position;// Light Position in eye coord.
    vec3 La;// Ambient light intensity
    vec3 Ld;// Diffuse light intensity
    vec3 Ls;// Specular light intensity
} light;

uniform MaterialInfo {
    vec3 Ka;// Ambient reflectivity
    vec3 Kd;// Diffuse reflectivity
    vec3 Ks;// Specular reflectivity
    float Shininess;// Specular shininess factor
} material;

layout (location = 0) out vec4 FragColor;

subroutine vec3 processLighting(vec3 pos, vec3 norm);
subroutine uniform processLighting lightProcessor;
subroutine(processLighting)
vec3 phongModel(vec3 pos, vec3 norm) {
    vec3 n = normalize( NormalMatrix_Frag * norm );
    vec4 camCoords = ModelViewMatrix_Frag * vec4(pos,1.0);
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
    return (ambient + diffuse + specular);
}
subroutine (processLighting)
vec3 blinnPhong(vec3 pos, vec3 norm) {
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

void main() {
    FragColor = vec4(lightProcessor(vPosition, vNormal), 1.0);
}
