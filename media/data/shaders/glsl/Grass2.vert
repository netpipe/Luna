// Sun light position
uniform vec3 mSunPos;
uniform vec3 windDir;
uniform float time;
varying float diffuse;
varying vec2 shadowTC;

float noiseR(float put,float lower, float upper) {
	return 1.0;//+clamp(cos(put)*cos(put*3.0)*cos(put*5.0)*cos(put*7.0)*3.0+sin(put*25.0)*0.3,-lower,upper);
}


float smooth(float x) {
	return x*x*(3.0-2.0*x);
}

float wind(float x) {
	return smooth(abs(fract(x+0.5)*2.0-1.0));
}

float MainWind(float x,float factor) {
	return (0.1+abs(sin(x*0.01021))*0.4+wind(x*0.2965)*0.5+wind(x*0.865)*0.5+sin(x*9.585)*0.09)*pow(factor,4.2)+sin((x+factor*0.35)*1.58845*windDir.y)*0.19*pow(factor,5.0);
}

float rotateWindDir(vec2 x) {
	return ((x.x+x.y)*cos(acos(windDir.z)-0.785549163)-(x.y-x.x)*sin(asin(windDir.x)+0.785549163))*0.06;
}

void main()
{
	if (gl_MultiTexCoord0.y < 0.99) {
		vec3 centr = gl_MultiTexCoord2.xyz;
		vec3 windOffset = vec3(windDir.x,0.0,windDir.z)*windDir.y*MainWind(time+rotateWindDir(gl_Vertex.xz),1.0-gl_MultiTexCoord0.y);
		vec3 vectorFromCenter = gl_Vertex.xyz-centr;
		windOffset = normalize(vectorFromCenter+windOffset);
		//vec3 normal = normalize(gl_Normal+windOffset); I cant figure out how to bend the normal
		vec4 tformed = vec4(centr+length(vectorFromCenter)*windOffset,gl_Vertex.w);
		gl_Position = gl_ModelViewProjectionMatrix * tformed;
		gl_FrontColor.a = clamp(exp2(-gl_Fog.density * length(gl_Position.xyz) * 1.442695), 0.0, 1.0);
		shadowTC = tformed.xz/vec2(1010.0,-1010.0)+vec2(0.51,0.51);
		diffuse = max(dot(normalize(mSunPos),gl_NormalMatrix*gl_Normal),0.0);
		gl_TexCoord[0] = gl_MultiTexCoord0;
	}
	else {
		gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
		gl_FrontColor.a = clamp(exp2(-gl_Fog.density * length(gl_Position.xyz) * 1.442695), 0.0, 1.0);
		shadowTC = gl_Vertex.xz/vec2(1010.0,-1010.0)+vec2(0.51,0.51);
		diffuse = max(dot(normalize(mSunPos),gl_NormalMatrix*gl_Normal),0.0);
		gl_TexCoord[0] = gl_MultiTexCoord0;
	}
}
