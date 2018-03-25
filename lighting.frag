#version 330 core

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

struct DirLight {
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct Light {
    vec3 position;
    vec3 direction;
    float innerCutOff;
    float outerCutOff;

    float constant;
    float linear;
    float quadratic;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;
uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 viewPos;
uniform Material material;
#define NR_LIGHTS 16
uniform bool lightEnables[NR_LIGHTS];
uniform Light lights[NR_LIGHTS];
uniform bool dirLightEnable;
uniform DirLight dirLight;

out vec4 FragColor;

vec3 calcPointLight(Light light, vec3 norm, vec3 fragPos, vec3 viewDir,
		vec3 sampDiffuse, vec3 sampSpecular)
{
   vec3 result = vec3(0.0);

   vec3 lightRelPos = light.position - fragPos;
   vec3 lightDir = normalize(lightRelPos);
   float theta = dot(lightDir, normalize(-light.direction));
   if (theta >= light.outerCutOff) {
   
      vec3 specular = vec3(0);
      float ddn = dot(lightDir, norm);
      if (ddn > 0.0) {
         vec3 reflectDir = -lightDir + 2 * norm * ddn;
         float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
         specular = light.specular * (spec * sampSpecular);
      }

      float diff = max(dot(norm, lightDir), 0.0);

      float epsilon = light.innerCutOff - light.outerCutOff;
      float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
      vec3 diffuse = sampDiffuse * (diff * light.diffuse);
      result = (diffuse + specular) * intensity;

      float dist2  = dot(lightRelPos, lightRelPos);
      float invatt = light.constant + light.linear * sqrt(dist2) + light.quadratic * dist2;
      result /= invatt;
   }
   return result + light.ambient * sampDiffuse;
}

vec3 calcDirLight(DirLight light, vec3 norm, vec3 viewDir,
		vec3 sampDiffuse, vec3 sampSpecular)
{
   vec3 lightDir = normalize(light.direction);

   float diff = max(dot(norm, lightDir), 0.0);
   vec3 diffuse = light.diffuse * (diff * sampDiffuse);

   vec3 specular = vec3(0);
   float ddn = dot(lightDir, norm);
   if (ddn > 0.0) {
      vec3 reflectDir = -lightDir + 2 * norm * ddn;
      float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
      specular = light.specular * (spec * sampSpecular);
   }

   return diffuse + specular + light.ambient * sampDiffuse;
}

void main()
{
   vec3 sampDiffuse = pow(texture(material.diffuse, TexCoords).xyz, vec3(2.2));
   vec3 sampSpecular = pow(texture(material.specular, TexCoords).xyz, vec3(2.2));

   vec3 norm = normalize(Normal);
   vec3 viewDir = normalize(viewPos - FragPos);

   vec3 result = vec3(0.0);
   if (dirLightEnable)
	   result = calcDirLight(dirLight, norm, viewDir, sampDiffuse, sampSpecular);

   for (int i = 0; i < NR_LIGHTS; i++) if (lightEnables[i]) {
       result += calcPointLight(lights[i], norm, FragPos, viewDir, sampDiffuse, sampSpecular);
   }

   FragColor = vec4(pow(result, vec3(1/2.2)), 1.0);
}
