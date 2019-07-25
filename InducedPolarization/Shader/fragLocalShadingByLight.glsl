
uniform vec3 uLightPos;//光源位置
uniform vec3 uViewPos;//相机位置

varying vec3 normal;
varying vec3 VerPosition;
varying vec4 verColor;

void main()
{
        if( gl_FrontFacing )
		{
            vec3 norm    = normalize(normal);
			vec3 lightv  = normalize(uLightPos - VerPosition);
			vec3 viewv   = normalize(uViewPos - VerPosition);
			vec3 halfv   = normalize(lightv + viewv);

			vec4 diffuse = vec4(0,0,0,1);
			vec4 ambient = vec4(0,0,0,1);
        
			diffuse = max(0, dot(halfv, norm)) * gl_LightSource[0].diffuse * verColor;
			ambient = gl_FrontMaterial.ambient * gl_LightSource[0].ambient * verColor;

			float f;
			if(dot(lightv, norm) >0)
				f = 1.0;
			else
				f = 0.0;
			vec4 specular   = f * pow(max(0.0, dot(norm, halfv)),50) * verColor * gl_LightSource[0].specular;
			vec3 color      = vec3(ambient.xyz + diffuse.xyz + specular.xyz);
			
			gl_FragColor    = vec4(color,1.0);
        }
		else
		{
            vec3 norm    = normalize(-normal);
            
			vec3 lightv  = normalize(uLightPos.xyz - VerPosition.xyz);
			vec3 viewv   = normalize(uViewPos - VerPosition);
			vec3 halfv   = normalize(lightv + viewv);

			vec4 diffuse = vec4(0,0,0,1);
			vec4 ambient = vec4(0,0,0,1);
        
			diffuse = max(0, (dot(viewv, norm))) * gl_LightSource[0].diffuse * verColor;
			ambient = gl_FrontMaterial.ambient * gl_LightSource[0].ambient * verColor;

			float f;
			if(dot(lightv, norm) >0)
				f = 1.0;
			else
				f = 0.0;
			vec4 specular   = f * pow(max(0.0, dot(norm, halfv)),50) * verColor * gl_LightSource[0].specular;
			vec3 color      = vec3(ambient.xyz + diffuse.xyz + specular.xyz);
			
			gl_FragColor    = vec4(color,1.0); 
        }   
}