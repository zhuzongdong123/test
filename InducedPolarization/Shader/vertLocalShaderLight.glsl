
uniform vec3 uLightPos;//��Դλ��
uniform vec3 uViewPos;//���λ��

varying vec3 normal;
varying vec3 VerPosition;
varying vec4 verColor;

void main()
{
	normal = gl_NormalMatrix  * gl_Normal;
    VerPosition = vec3(gl_ModelViewMatrix * gl_Vertex);
	verColor = gl_Color;

	gl_Position = ftransform();
}