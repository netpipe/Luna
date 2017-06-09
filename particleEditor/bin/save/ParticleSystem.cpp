//! ---------------------------------------------------------------------------------
//! Particle system ID: 0
//! Particle system name: smoke

	scene::IParticleSystemSceneNode* p = scenemgr->addParticleSystemSceneNode();

	p->setParticleSize(core::dimension2d<f32>(5.0f, 5.0f));

	scene::IParticleEmitter* em = p->createBoxEmitter(
	        core::aabbox3d<f32>(-2,-1,-2,2,1,2),
	        core::vector3df(0.000f,0.006f,0.000f),
	        100,250, video::SColor(0, 0, 0, 0),video::SColor(0, 40, 40, 40), 800, 2000);
        
	p->setEmitter(em); 
	em->drop();

	scene::IParticleAffector* paf = p->createFadeOutParticleAffector();
	p->addAffector(paf);
	paf->drop();

	ps->setMaterialFlag(video::EMF_LIGHTING, false);
	ps->setMaterialTexture(0, driver->getTexture("D:\Dev\Irrlicht Particle Editor\bin\textures\particles\ParticleFire.tga"));
	ps->setMaterialType(video::TRANSPARENT_VERTEX_ALPHA);

//! ---------------------------------------------------------------------------------
//! Particle system ID: 1
//! Particle system name: fire

	scene::IParticleSystemSceneNode* p = scenemgr->addParticleSystemSceneNode();

	p->setParticleSize(core::dimension2d<f32>(3.0f, 3.0f));

	scene::IParticleEmitter* em = p->createBoxEmitter(
	        core::aabbox3d<f32>(-2,-1,-2,2,1,2),
	        core::vector3df(0.000f,0.006f,0.000f),
	        80,100, video::SColor(0, 125, 83, 85),video::SColor(0, 255, 146, 0), 800, 2000);
        
	p->setEmitter(em); 
	em->drop();

	scene::IParticleAffector* paf = p->createFadeOutParticleAffector();
	p->addAffector(paf);
	paf->drop();

	ps->setMaterialFlag(video::EMF_LIGHTING, false);
	ps->setMaterialTexture(0, driver->getTexture("D:\Dev\Irrlicht Particle Editor\bin\textures\particles\ParticleFire.tga"));
	ps->setMaterialType(video::TRANSPARENT_VERTEX_ALPHA);

