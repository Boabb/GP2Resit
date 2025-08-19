#version 400

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;
out vec4 FragColor;

uniform sampler2D textureSampler;

uniform vec3 lightDir;
uniform vec3 lightColor;
uniform vec3 ambientColor;

void main()
{
    vec3 norm = normalize(Normal);

    float diff = max(dot(norm, -lightDir), 0.0);
    vec3 lighting = ambientColor + diff * lightColor;

    vec4 texColor = texture(textureSampler, TexCoord);

    FragColor = vec4(lighting * texColor.rgb, texColor.a);
}
