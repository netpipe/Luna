#ifndef PARTICLESYSTEM_H
#define PARTICLESYSTEM_H

#include "globals.hxx"

class ParticleSystem
{
  public:

    ParticleSystem(
      ISceneManager &pSceneManager,
      IVideoDriver &pVideoDriver,
      vector3df pParticlePosition = vector3df(0,0,0)
      );

    void updateParticleSystem(void);
    void initializeSystem(void);
    void createEmitter(void);
    void createAffectors(void);
    void addParticleSystem(vector3df pos);
    void addPreset(wchar_t *name);
    void addPreset(PRESET &preset);
    void setPreset(s32 id);
    void setPresetName(wchar_t *name) {
      presetNames.push_back(name);
      presetNamesIndex++;
      printf("Preset name set to: %S index: %i\n", name, presetNamesIndex);
    }

    void deleteCurrentSystem(void);

    virtual ~ParticleSystem();

    void clearPresets(void){
      m_aPresets.clear();
      presetNames.clear();
      presetNamesIndex = -1;
      printf("Cleared presets. m_aPresets.size = %i, presetNames.size = %i\n", m_aPresets.size(), presetNames.size());
    }

    s32   getCurrentID(void){ return m_ID; }
    s32   getParticleSystemCount(void){ return m_iParticleSystemCount; }
    void  setCurrentID(s32 _id) {
      m_ID = _id;
      showCurrentBBox();
      m_pParticle = m_aParticles[m_ID];
      m_pEmitter = m_aEmitters[m_ID];
      m_pAffector = m_aAffectors[m_ID];
    }

    //! Show bbox for currently active particle system.
    void  showCurrentBBox(void);

    //! --------------------------------------
    //! Particle helper functions.
    //! --------------------------------------
    __inline void
    setParticleSystemScale(vector3df &scale){
      m_pParticle.scale = scale;
    }
    __inline vector3df
    getParticleSystemScale(void){
      return m_pParticle.scale;
    }

    __inline void
    setParticleSize(dimension2d<f32> &size){
      m_pParticle.size = size;
    }

    __inline vector3df getParticlePosition(void){
      return m_pParticle.position;
    }

    __inline E_MATERIAL_TYPE getParticleMaterialType(void)
    {
      return m_pParticle.materialType;
    }

    __inline void
    setParticleTexture(stringc texture, bool preset);

    __inline stringc
    &getParticleTexture(void){
      return m_particleTexture;
    }

    __inline void setParticleScaleX(float scale){
      m_pParticle.scale.X = scale;
    }
    __inline void setParticleScaleY(float scale){
      m_pParticle.scale.Y = scale;
    }
    __inline void setParticleScaleZ(float scale){
      m_pParticle.scale.Z = scale;
    }

    __inline void setMaterialType(E_MATERIAL_TYPE type){
      m_pParticle.materialType = type;
    }
    __inline E_MATERIAL_TYPE getMaterialType(void){
      return m_pParticle.materialType;
    }

    __inline void setParticleSizeX(float scale){
      m_pParticle.size.Width = scale;
    }
    __inline void setParticleSizeY(float scale){
      m_pParticle.size.Height = scale;
    }
    __inline float getParticleSizeX(void){
      return m_pParticle.size.Width;
    }
    __inline float getParticleSizeY(void){
      return m_pParticle.size.Height;
    }

    __inline void setParticlePositionX(float pos){
      m_vParticleSystemPosition[m_ID].X = pos;
      //m_pParticle.position.X = pos;
    }
    __inline void setParticlePositionY(float pos){
      m_vParticleSystemPosition[m_ID].Y = pos;
      //m_pParticle.position.Y = pos;
    }
    __inline void setParticlePositionZ(float pos){
      m_vParticleSystemPosition[m_ID].Z = pos;
      //m_pParticle.position.Z = pos;
    }

    //! --------------------------------------
    //! Emitter helper functions.
    //! --------------------------------------
    __inline void
    setEmitterMinStartColor(SColor color){
      m_pEmitter.minStartColor = color;
    }

    __inline SColor
    getEmitterMinStartColor(void){
      return m_pEmitter.minStartColor;
    }

    __inline void
    setEmitterMaxStartColor(SColor color){
      m_pEmitter.maxStartColor = color;
    }

    __inline SColor
    getEmitterMaxStartColor(void){
      return m_pEmitter.maxStartColor;
    }

    __inline aabbox3d<f32>
    setEmitterBox(int width, int height, int length){
      m_eBoxWidth = width;
      m_eBoxHeight = height;
      m_eBoxLength = length;

      return m_pEmitter.emitterBox = aabbox3d<f32>(-width/2, 0, -length/2, width/2, height, length/2);
    }

    __inline int getEmitterBoxWidth(void){
      return m_eBoxWidth;
    }
    __inline int getEmitterBoxHeight(void){
      return m_eBoxHeight;
    }
    __inline int getEmitterBoxLength(void){
      return m_eBoxLength;
    }

    __inline void setEmitterDirectionX(float x){
      m_pEmitter.direction = vector3df(x,m_pEmitter.direction.Y,m_pEmitter.direction.Z);
    }
    __inline void setEmitterDirectionY(float y){
      m_pEmitter.direction = vector3df(m_pEmitter.direction.X,y,m_pEmitter.direction.Z);
    }
    __inline void setEmitterDirectionZ(float z){
      m_pEmitter.direction = vector3df(m_pEmitter.direction.X,m_pEmitter.direction.Y,z);
    }
    __inline vector3df getEmitterDirection(void){
      return m_pEmitter.direction;
    }

    __inline void setEmitterParticlesMin(u32 min){
      m_pEmitter.minParticlesPerSecond = min;
    }
    __inline void setEmitterParticlesMax(u32 max){
      m_pEmitter.maxParticlesPerSecond = max;
    }
    __inline u32 getEmitterParticleMin(void){
      return m_pEmitter.minParticlesPerSecond;
    }
    __inline u32 getEmitterParticleMax(void){
      return m_pEmitter.maxParticlesPerSecond;
    }

    __inline void setEmitterParticlesLifeMin(u32 min){
      m_pEmitter.lifeTimeMin = min;
    }
    __inline void setEmitterParticlesLifeMax(u32 max){
      m_pEmitter.lifeTimeMax = max;
    }
    __inline int getEmitterParticlesLifeMin(void){
      return m_pEmitter.lifeTimeMin;
    }
    __inline int getEmitterParticlesLifeMax(void){
      return m_pEmitter.lifeTimeMax;
    }

    __inline float getEmitterMaxAngleDegrees(void){
      return m_pEmitter.maxAngleDegrees;
    }
    __inline void setEmitterMaxAngleDegrees(s32 degrees){
      m_pEmitter.maxAngleDegrees = degrees;
    }

    __inline aabbox3d<f32>
    getEmitterBox(void){
      return m_pEmitter.emitterBox;
    }

    //! --------------------------------------
    //! Affector helper functions.
    //! --------------------------------------
    /*
    struct PARTICLE_AFFECTOR
    {
      //! Holds variables for both gravity and fade out.
      SColor targetColor;
      u32 timeNeededToFadeOut;

      vector3df gravity;
      u32 timeForceLost;
    };
    */
    //! Get helpers.
      __inline SColor getAffectorTargetColor(void){
        return m_pAffector.targetColor;
      }
      __inline u32 getAffectorFadeOutTime(void){
        return m_pAffector.timeNeededToFadeOut;
      }
      __inline vector3df getAffectorGravity(void){
        return m_pAffector.gravity;
      }
      __inline u32 getAffectorTimeForceLost(void){
        return m_pAffector.timeForceLost;
      }
    //! Set helpers.
      __inline void setAffectorTargetColor(SColor col){
        m_pAffector.targetColor = col;
      }
      __inline void setAffectorFadeOutTime(u32 time){
        m_pAffector.timeNeededToFadeOut = time;
      }
      __inline void setAffectorGravity(vector3df gravity){
        m_pAffector.gravity = gravity;
      }
      __inline void setAffectorTimeForceLost(u32 time){
        m_pAffector.timeForceLost = time;
      }

    //! --------------------------------------
    //! End helpers.
    //! --------------------------------------

    array<PRESET> m_aPresets;
    array<stringw> presetNames;
    int presetNamesIndex;

    void setWorkDir(stringc dir){
      workDir = dir;
      printf("[PS] Workdir: %s\n", workDir.c_str());
    }

  protected:
  private:

    stringc workDir;

    //! ID of currently active particle system.
    s32 m_ID;

    int m_eBoxWidth;
    int m_eBoxHeight;
    int m_eBoxLength;

    //! Particle emitter variables.
    struct PARTICLE_SYSTEM
    {
      IParticleSystemSceneNode  *m_particleSystem;
      IParticleEmitter          *m_particleEmitter;
      IParticleAffector         *m_particleAffectorGravity;
      IParticleAffector         *m_particleAffectorFadeOut;
    };
    array<PARTICLE_SYSTEM> m_aParticleSystem;
    s32 m_iParticleSystemCount;
    array<vector3df> m_vParticleSystemPosition;  //! For storing current position.

    ISceneManager *m_irrSceneManager;
    IVideoDriver  *m_irrVideoDriver;

    stringc m_particleTexture;

    PARTICLE_EMITTER  m_pEmitter;
    PARTICLE          m_pParticle;
    PARTICLE_AFFECTOR m_pAffector;

    array<PARTICLE_EMITTER>   m_aEmitters;
    array<PARTICLE>           m_aParticles;
    array<PARTICLE_AFFECTOR>  m_aAffectors;
};

#endif // PARTICLESYSTEM_H
