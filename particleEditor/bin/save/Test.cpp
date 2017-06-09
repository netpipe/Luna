//! ---------------------------------------------------------------------------------
//! Particle system ID: 0
//! Particle system name: test

	scene::IParticleSystemSceneNode* p = scenemgr->addParticleSystemSceneNode();

	p->setParticleSize(core::dimension2d<f32>(2.0f, 2.0f));

	scene::IParticleEmitter* em = p->createBoxEmitter(
	        core::aabbox3d<f32>(-2,-1,-1,2,1,1),
	        core::vector3df(0.000f,0.006f,0.000f),
	        80,100, video::SColor(0, 255, 255, 255),video::SColor(0, 255, 255, 255), 800, 2000);
        
	p->setEmitter(em); 
	em->drop();

	scene::IParticleAffector* paf = p->createFadeOutParticleAffector();
	p->addAffector(paf);
	paf->drop();

	ps->setMaterialFlag(video::EMF_LIGHTING, false);
	ps->setMaterialTexture(0, driver->getTexture("D:\Dev\Irrlicht Particle Editor\bin\textures\particles\ParticleFire.tga"));
	ps->setMaterialType(video::TRANSPARENT_VERTEX_ALPHA);

