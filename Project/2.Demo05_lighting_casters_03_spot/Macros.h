/*
 * Macros.h
 *
 * Created by zhouruibin734 on 2020/07/22.
 * Copyright (c) 2020年 zhouruibin734 All rights reserved.
 */

#ifndef MACROS_H
#define MACROS_H

#include <string>

const std::string objectVShaderSource = R"(

#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    FragPos = vec3(model * vec4(aPos, 1.0));
    Normal = mat3(transpose(inverse(model))) * aNormal;
    TexCoords = aTexCoords;
    
    gl_Position = projection * view * vec4(FragPos, 1.0);
}

)";


const std::string objectFShaderSource = R"(

#version 330 core
out vec4 FragColor;

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

struct Light {
    vec3 position;
    vec3 direction;
    float cutOff;
    float outerCutOff;
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    
    float constant;
    float linear;
    float quadratic;
};

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;
  
uniform vec3 viewPos;
uniform Material material;
uniform Light light;

void main()
{
    vec3 lightDir = normalize(light.position - FragPos);
    
    // check if lighting is inside the spotlight cone
    float theta = dot(lightDir, normalize(-light.direction));
    
    if(theta > light.cutOff) // remember that we're working with angles as cosines instead of degrees so a '>' is used.
    {
        // ambient
        vec3 ambient = light.ambient * texture(material.diffuse, TexCoords).rgb;
        
        // diffuse
        vec3 norm = normalize(Normal);
        float diff = max(dot(norm, lightDir), 0.0);
        vec3 diffuse = light.diffuse * diff * texture(material.diffuse, TexCoords).rgb;
        
        // specular
        vec3 viewDir = normalize(viewPos - FragPos);
        vec3 reflectDir = reflect(-lightDir, norm);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
        vec3 specular = light.specular * spec * texture(material.specular, TexCoords).rgb;
        
        // attenuation
        float distance    = length(light.position - FragPos);
        float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

        // ambient  *= attenuation; // remove attenuation from ambient, as otherwise at large distances the light would be darker inside than outside the spotlight due the ambient term in the else branche
        diffuse   *= attenuation;
        specular *= attenuation;
            
        vec3 result = ambient + diffuse + specular;
        FragColor = vec4(result, 1.0);
    }
    else
    {
        // else, use ambient light so scene isn't completely dark outside the spotlight.
        FragColor = vec4(light.ambient * texture(material.diffuse, TexCoords).rgb, 1.0);
    }
} 

)";

const std::string lightVShaderSource = R"(

#version 330 core
layout (location = 0) in vec3 aPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0);
}

)";


const std::string lightFShaderSource = R"(

#version 330 core
out vec4 FragColor;

void main()
{
    FragColor = vec4(1.0); // set alle 4 vector values to 1.0
}

)";


#endif /* !MACROS_H */
