//! ---------------------------------------------------------------------------------
//! Particle system ID: 0
//! Particle system name: wf_base_1

	scene::IParticleSystemSceneNode* p = scenemgr->addParticleSystemSceneNode();

	p->setParticleSize(core::dimension2d<f32>(5.0f, 4.0f));

	scene::IParticleEmitter* em = p->createBoxEmitter(
	        core::aabbox3d<f32>(-1,-1,-1,1,1,1),
	        core::vector3df(0.000f,0.006f,0.003f),
	        250,400, video::SColor(0, 0, 0, 0),video::SColor(0, 41, 74, 90), 1500, 3500);
        
	p->setEmitter(em); 
	em->drop();

	scene::IParticleAffector* paf = p->createFadeOutParticleAffector();
	p->addAffector(paf);
	paf->drop();

	ps->setMaterialFlag(video::EMF_LIGHTING, false);
	ps->setMaterialTexture(0, driver->getTexture("D:\Dev\My Projects\Irrlicht Particle Editor\bin\textures\particles\Dee_FX_64x64_25.tga"));
	ps->setMaterialType(video::TRANSPARENT_VERTEX_ALPHA);

//! ---------------------------------------------------------------------------------
//! Particle system ID: 1
//! Particle system name: wf_base_2

	scene::IParticleSystemSceneNode* p = scenemgr->addParticleSystemSceneNode();

	p->setParticleSize(core::dimension2d<f32>(5.0f, 4.0f));

	scene::IParticleEmitter* em = p->createBoxEmitter(
	        core::aabbox3d<f32>(-1,-1,-1,1,1,1),
	        core::vector3df(0.000f,0.006f,0.003f),
	        250,400, video::SColor(0, 0, 0, 0),video::SColor(0, 41, 74, 90), 1500, 3500);
        
	p->setEmitter(em); 
	em->drop();

	scene::IParticleAffector* paf = p->createFadeOutParticleAffector();
	p->addAffector(paf);
	paf->drop();

	ps->setMaterialFlag(video::EMF_LIGHTING, false);
	ps->setMaterialTexture(0, driver->getTexture("D:\Dev\My Projects\Irrlicht Particle Editor\bin\textures\particles\Dee_FX_64x64_25.tga"));
	ps->setMaterialType(video::TRANSPARENT_VERTEX_ALPHA);

//! ---------------------------------------------------------------------------------
//! Particle system ID: 2
//! Particle system name: wf_base_3

	scene::IParticleSystemSceneNode* p = scenemgr->addParticleSystemSceneNode();

	p->setParticleSize(core::dimension2d<f32>(5.0f, 4.0f));

	scene::IParticleEmitter* em = p->createBoxEmitter(
	        core::aabbox3d<f32>(-1,-1,-1,1,1,1),
	        core::vector3df(0.000f,0.006f,0.003f),
	        250,400, video::SColor(0, 0, 0, 0),video::SColor(0, 41, 74, 90), 1500, 3500);
        
	p->setEmitter(em); 
	em->drop();

	scene::IParticleAffector* paf = p->createFadeOutParticleAffector();
	p->addAffector(paf);
	paf->drop();

	ps->setMaterialFlag(video::EMF_LIGHTING, false);
	ps->setMaterialTexture(0, driver->getTexture("D:\Dev\My Projects\Irrlicht Particle Editor\bin\textures\particles\Dee_FX_64x64_25.tga"));
	ps->setMaterialType(video::TRANSPARENT_VERTEX_ALPHA);

//! ---------------------------------------------------------------------------------
//! Particle system ID: 3
//! Particle system name: wf_base_4

	scene::IParticleSystemSceneNode* p = scenemgr->addParticleSystemSceneNode();

	p->setParticleSize(core::dimension2d<f32>(5.0f, 4.0f));

	scene::IParticleEmitter* em = p->createBoxEmitter(
	        core::aabbox3d<f32>(-1,-1,-1,1,1,1),
	        core::vector3df(0.000f,0.006f,0.003f),
	        250,400, video::SColor(0, 0, 0, 0),video::SColor(0, 41, 74, 90), 1500, 3500);
        
	p->setEmitter(em); 
	em->drop();

	scene::IParticleAffector* paf = p->createFadeOutParticleAffector();
	p->addAffector(paf);
	paf->drop();

	ps->setMaterialFlag(video::EMF_LIGHTING, false);
	ps->setMaterialTexture(0, driver->getTexture("D:\Dev\My Projects\Irrlicht Particle Editor\bin\textures\particles\Dee_FX_64x64_25.tga"));
	ps->setMaterialType(video::TRANSPARENT_VERTEX_ALPHA);

//! ---------------------------------------------------------------------------------
//! Particle system ID: 4
//! Particle system name: wf_base_5

	scene::IParticleSystemSceneNode* p = scenemgr->addParticleSystemSceneNode();

	p->setParticleSize(core::dimension2d<f32>(5.0f, 4.0f));

	scene::IParticleEmitter* em = p->createBoxEmitter(
	        core::aabbox3d<f32>(-1,-1,-1,1,1,1),
	        core::vector3df(0.000f,0.006f,0.003f),
	        250,400, video::SColor(0, 0, 0, 0),video::SColor(0, 41, 74, 90), 1500, 3500);
        
	p->setEmitter(em); 
	em->drop();

	scene::IParticleAffector* paf = p->createFadeOutParticleAffector();
	p->addAffector(paf);
	paf->drop();

	ps->setMaterialFlag(video::EMF_LIGHTING, false);
	ps->setMaterialTexture(0, driver->getTexture("D:\Dev\My Projects\Irrlicht Particle Editor\bin\textures\particles\Dee_FX_64x64_25.tga"));
	ps->setMaterialType(video::TRANSPARENT_VERTEX_ALPHA);

