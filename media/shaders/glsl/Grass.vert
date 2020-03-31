/*/ simple vertex shader
varying vec4 centr;
varying mat3 Rx1;
varying vec4 tformed;
uniform float mFar;
uniform float decay;
uniform float instances;
uniform vec3 windDir;
uniform float time;

float smooth(float x) {
	return x*x*(3.0-2.0*x);
}

float wind(float x) {
	return smooth(abs(fract(x+0.5)*2.0-1.0));
}

float MainWind(float x,float factor) {
	return (0.1+abs(sin(x*0.01021))*0.35+wind(x*0.2965)*0.5+wind(x*0.865)*0.5+sin(x*9.585)*0.09)*pow(factor,4.2)+sin((x+factor*0.35)*1.58845*windDir.y)*0.19*pow(factor,5.0);
}

float rotateWindDir(vec2 x) {
	return ((x.x+x.y)*cos(acos(windDir.z)-0.785549163)-(x.y-x.x)*sin(asin(windDir.x)+0.785549163))*0.04;
}

#define IDENTITYMAT3 mat3(vec3(1.0,0.0,0.0),vec3(0.0,1.0,0.0),vec3(0.0,0.0,1.0))

void main()
{
	vec3 normal = normalize(gl_MultiTexCoord1.xyz);
	centr = vec4(gl_MultiTexCoord2.xyz,1.0);
	vec4 transNodePos = gl_ModelViewProjectionMatrix*centr;
	float Radius = length(gl_MultiTexCoord1.xyz);
	if ((abs(transNodePos.x)-Radius)/transNodePos.z>1.0||(abs(transNodePos.y)-Radius)/transNodePos.z>1.0&&(length(transNodePos.xyz)/Radius>1.0)) {
		gl_Position = vec4(0.0);
		centr.w = 0.0;
	}
	else {
		vec3 windOffset = vec3(windDir.x,0.0,windDir.z)*windDir.y*MainWind(time+rotateWindDir(gl_Vertex.xz),1.0-gl_MultiTexCoord0.y);
		vec3 vectorFromCenter = gl_Vertex.xyz-centr;
		windOffset = normalize(vectorFromCenter+windOffset);
		float d = length(normal.yz);
		float cd = normal.z/d;
		float bd = normal.y/d;
		Rx1 = IDENTITYMAT3;
		mat3 Rx = IDENTITYMAT3;
		if (cd>0.0||bd>0.0) {
			Rx1 = mat3(vec3(1.0,0.0,0.0),vec3(0.0,cd,bd),vec3(0.0,-bd,cd));
			Rx = mat3(vec3(1.0,0.0,0.0),vec3(0.0,cd,-bd),vec3(0.0,bd,cd));
		}
		d = length(normal.xz);
		cd = normal.z/d;
		bd = normal.x/d;
		if (cd>0.0||bd>0.0) {
			Rx1 *= mat3(vec3(cd,0.0,bd),vec3(0.0,1.0,0.0),vec3(-bd,0.0,cd));
			Rx = mat3(vec3(cd,0.0,-bd),vec3(0.0,1.0,0.0),vec3(bd,0.0,cd))*Rx;
		}
		tformed = vec4((gl_ModelViewProjectionMatrix*vec4(centr+length(vectorFromCenter)*windOffset,1.0)).xyz,1.0);//length((gl_ModelViewProjectionMatrix*centr).xyz)/length(gl_MultiTexCoord1.xyz));
		gl_Position    = vec4(Rx*(gl_Vertex.xyz-centr.xyz),gl_Vertex.w);
		gl_FrontColor.x  = clamp(exp2(-gl_Fog.density * length(tformed.xyz) * 1.442695), 0.0, 1.0);
		gl_TexCoord[0] = gl_MultiTexCoord0;
		if (normal.y!=1.0)
			centr.w = floor(instances*0.75)+1.0;
		else
			centr.w = floor(min(pow(1.0292-length(tformed.xyz/mFar/1.683),decay),1.0)*instances)+1.0;
	}
}
*/

uniform vec3 mSunPos;
uniform vec3 windDir;
uniform float time;

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
	vec3 centr = gl_MultiTexCoord2.xyz;
	//vec3 transNodePos = centr-vec3(-75.0,-10.0,17.0);//(gl_ModelViewProjectionMatrix*vec4(centr,1.0)).xyz;
	float Radius = gl_MultiTexCoord1.x;
	if (/*(abs(transNodePos.x)-Radius)/transNodePos.z>1.0||(abs(transNodePos.y)-Radius)/transNodePos.z>1.0&&*/length(centr-vec3(-300,6.0,200.0))<22.0) {
		gl_Position = vec4(0.0);
		gl_FrontColor = vec4(0.0);
	}
	else if (gl_MultiTexCoord0.y < 0.99) {
		vec3 windOffset = vec3(windDir.x,0.0,windDir.z)*windDir.y*MainWind(time+rotateWindDir(gl_Vertex.xz),1.0-gl_MultiTexCoord0.y);
		vec3 vectorFromCenter = gl_Vertex.xyz-centr;
		windOffset = normalize(vectorFromCenter+windOffset);
		vec4 tformed = vec4(centr+length(vectorFromCenter)*windOffset,gl_Vertex.w);
		gl_Position = gl_ModelViewProjectionMatrix * tformed;
		gl_FrontColor = vec4(max(dot(normalize(mSunPos),gl_NormalMatrix*gl_Normal),0.0),1.0,0.0,clamp(exp2(-gl_Fog.density * length(gl_Position.xyz) * 1.442695), 0.0, 1.0));
		gl_TexCoord[0] = vec4(gl_MultiTexCoord0.xy,gl_Vertex.xz/vec2(1010.0,-1010.0)+vec2(0.51,0.51));
	}
	else {
		gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
		gl_FrontColor = vec4(max(dot(normalize(mSunPos),gl_NormalMatrix*gl_Normal),0.0),1.0,0.0,clamp(exp2(-gl_Fog.density * length(gl_Position.xyz) * 1.442695), 0.0, 1.0));
		gl_TexCoord[0] = vec4(gl_MultiTexCoord0.xy,gl_Vertex.xz/vec2(1010.0,-1010.0)+vec2(0.51,0.51));
	}
}
