PyMethodDef irr_Sound[] =
{
    {"fluidsynth",Python::PyIrr_FluidSynth,METH_VARARGS,"fluidsynth"},
    {"soundman",Python::PyIrr_SoundMan,METH_VARARGS,"PyIrr_SoundMan"},


	{NULL,NULL,0,NULL}
};

PyObject * Python::PyIrr_SoundMan(PyObject * self,PyObject * args){ //active camera

    int param,state,sound,ammount;
    PyArg_ParseTuple(args,"liii",&sound,&param,&ammount,&state);

    #ifdef DSOUND
    // sound intensity for raycasted sound.  // surfaceRoughnessHardness/propigation factor, distance,handle
    switch (param){
    case 0:
//        managerID = cAudio::createAudioManager(true);  // broken has to be done from main
       if( managerID)
        {
         //   luna->manager->initialize(luna->manager->getAvailableDeviceName(0));
           mysound = managerID->create("bling","./media/bling.ogg",false);
    //        return Py_BuildValue("l",manager
            mysound->play2d(true);
        }

       return Py_BuildValue("l",managerID);
        //break;
    case 1:
            mysound = managerID->create("bling","./media/bling.ogg",false);

       return Py_BuildValue("l",mysound);
        break;
    }
    #endif
return Py_BuildValue("l",managerID);
}// make add sound method

PyObject * Python::PyIrr_FluidSynth(PyObject * self,PyObject * args){ //active camera
//
////http://www.fluidsynth.org/api/index.html#MIDIPlayerMem
//    int typee;
//    char * sound;
//    char * param;
//    PyArg_ParseTuple(args,"ssi",&sound,&param,&typee);
//#define NETWORK_SUPPORT
//
//	//char *psoundfont ="soundfonts/VintageDreamsWaves-v2.sf2";
//		char *psoundfont =sound;
//	//char *psong = "BLUES.MID";
//     char *psong = param;
//
//
//if( typee==0 ){
//
//
//
//     //   int param,state,sound,ammount;
//   // PyArg_ParseTuple(args,"liii",&sound,&param,&ammount,&state);
//   //load unload
//     fluid_settings_t* settings;
////  int arg1 = 1;
//  char buf[512];
////  int c, i;
//  int interactive = 1;
//  int midi_in = 1;
//
//#ifdef NETWORK_SUPPORT
//  fluid_server_t* server = NULL;
//  int with_server = 0;
//#endif
//  char* config_file = NULL;
//  int audio_groups = 0;
//  int audio_channels = 0;
//  int dump = 0;
//  int fast_render = 0;
//  static const char optchars[] = "a:C:c:dE:f:F:G:g:hijK:L:lm:nO:o:p:R:r:sT:Vvz:";
//#ifdef LASH_ENABLED
//  int connect_lash = 1;
//  int enabled_lash = 0;		/* set to TRUE if lash gets enabled */
//  fluid_lash_args_t *lash_args;
//
//  lash_args = fluid_lash_extract_args (&argc, &argv);
//#endif
//
//
//
//  settings = new_fluid_settings();
//
//
// /* The 'groups' setting is relevant for LADSPA operation and channel mapping
//   * in rvoice_mixer.
//   * If not given, set number groups to number of audio channels, because
//   * they are the same (there is nothing between synth output and 'sound card')
//   */
//  if ((audio_groups == 0) && (audio_channels != 0)) {
//      audio_groups = audio_channels;
//  }
//  if (audio_groups != 0)
//  {
//      fluid_settings_setint(settings, "synth.audio-groups", audio_groups);
//  }
//
//  if (fast_render) {
//    midi_in = 0;
//    interactive = 0;
//#ifdef NETWORK_SUPPORT
//    with_server = 0;
//#endif
//    fluid_settings_setstr(settings, "player.timing-source", "sample");
//    fluid_settings_setint(settings, "synth.lock-memory", 0);
//  }
//
//  /* create the synthesizer */
//  synth = new_fluid_synth(settings);
//  if (synth == NULL) {
//    fprintf(stderr, "Failed to create the synthesizer\n");
//    exit(-1);
//  }
//
//
//  /* load the soundfonts (check that all non options are SoundFont or MIDI files) */
////  for (i = arg1; i < argc; i++) {
//    if (fluid_is_soundfont(psoundfont))
//    {
//      if (fluid_synth_sfload(synth, psoundfont, 1) == -1)
//	fprintf(stderr, "Failed to load the SoundFont %s\n", psoundfont);
//    }
//    else if (!fluid_is_midifile(psoundfont))
//      fprintf (stderr, "Parameter '%s' not a SoundFont or MIDI file or error occurred identifying it.\n",
//	       psoundfont);
//
//
//  /* start the synthesis thread */
//  if (!fast_render) {
//		fluid_settings_setstr(settings, "audio.driver", "alsa");
//    adriver = new_fluid_audio_driver(settings, synth);
//    if (adriver == NULL) {
//      fprintf(stderr, "Failed to create the audio driver\n");
////      goto cleanup;
//    }
//  }
//
//
//  /* start the midi router and link it to the synth */
//#if WITH_MIDI
//  if (midi_in) {
//    /* In dump mode, text output is generated for events going into and out of the router.
//     * The example dump functions are put into the chain before and after the router..
//     */
//    //sequencer = new_fluid_sequencer2(0);
//
//    router = new_fluid_midi_router(
//      settings,
//      dump ? fluid_midi_dump_postrouter : fluid_synth_handle_midi_event,
//      (void*)synth);
//
//    if (router == NULL) {
//      fprintf(stderr, "Failed to create the MIDI input router; no MIDI input\n"
//	      "will be available. You can access the synthesizer \n"
//	      "through the console.\n");
//    } else {
//      mdriver = new_fluid_midi_driver(
//	settings,
//	dump ? fluid_midi_dump_prerouter : fluid_midi_router_handle_midi_event,
//	(void*) router);
//      if (mdriver == NULL) {
//	fprintf(stderr, "Failed to create the MIDI thread; no MIDI input\n"
//		"will be available. You can access the synthesizer \n"
//		"through the console.\n");
//      }
//    }
//  }
//#endif
//
//  /* play the midi fildes, if any */
////  for (i = arg1; i < argc; i++) {
//    if  (fluid_is_midifile(psong)) {
//
//      if (player == NULL) {
//	player = new_fluid_player(synth);
//	if (player == NULL) {
//	  fprintf(stderr, "Failed to create the midifile player.\n"
//		  "Continuing without a player.\n");
//	//  break;
//	}
//      }
//
//      fluid_player_add(player, psong);
//    }
// // }
//
//  if (player != NULL) {
//
//    if (fluid_synth_get_sfont(synth, 0) == NULL) {
//      /* Try to load the default soundfont if no soundfont specified */
//      char *s;
//      if (fluid_settings_dupstr(settings, "synth.default-soundfont", &s) != FLUID_OK)
//        s = NULL;
//      if ((s != NULL) && (s[0] != '\0'))
//        fluid_synth_sfload(synth, s, 1);
//
/////      FLUID_FREE(s);
//    }
//   //  fluid_player_set_bpm (player,125);
//
//   // fluid_player_set_loop(player,5);
//  //  fluid_player_play(player);
//    //fluid_player_set_midi_tempo(player,480000);
////fluid_player_join(player);
//  }
//
//
//  cmd_handler = new_fluid_cmd_handler(synth, router);
//  if (cmd_handler == NULL) {
//    fprintf(stderr, "Failed to create the command handler\n");
// //   goto cleanup;
//  }
//
//  /* try to load the user or system configuration */
//  if (config_file != NULL) {
//    fluid_source(cmd_handler, config_file);
//  } else if (fluid_get_userconf(buf, sizeof(buf)) != NULL) {
//    fluid_source(cmd_handler, buf);
//  } else if (fluid_get_sysconf(buf, sizeof(buf)) != NULL) {
//    fluid_source(cmd_handler, buf);
//  }
//
//  /* run the server, if requested */
//#ifdef NETWORK_SUPPORT
//  if (with_server) {
//    server = new_fluid_server(settings, synth, router);
//    if (server == NULL) {
//      fprintf(stderr, "Failed to create the server.\n"
//	     "Continuing without it.\n");
//    }
//  }
//#endif
//
//#ifdef LASH_ENABLED
//  if (enabled_lash)
//    fluid_lash_create_thread (synth);
//#endif
//
////          fluid_player_play(player);
//}
//
//else if (typee == 1){
////fluid_player_stop(player);
////fluid_player_join(player);
//
//            /* Play a note */
//        fluid_synth_noteon(synth, 0, 60, 100);
//}
//else if (typee == 2){
//fluid_player_stop(player);
////fluid_player_join(player);
//
//}
//
//else if (typee == 3){
//    //        printf("ready and playing");
//  //          fluid_player_stop(player);
////        fluid_player_join(player);
//if (fluid_player_get_status(player) == FLUID_PLAYER_READY )
//{
//    printf("ready and playing");
//
//        fluid_player_add(player,param);
//        fluid_player_play(player);
//    }
//if (fluid_player_get_status(player) == FLUID_PLAYER_DONE )
//{
//    printf("done and replaying");
//
//        fluid_player_add(player,param);
//        fluid_player_play(player);
//    }
////if  (fluid_is_midifile(psong)) {
////
////      if (player == NULL) {
////	player = new_fluid_player(synth);
////	if (player == NULL) {
////	  fprintf(stderr, "Failed to create the midifile player.\n"
////		  "Continuing without a player.\n");
////	//  break;
////	}
////      }
////
////      fluid_player_add(player, psong);
////          fluid_player_play(player);
////    }
//
//
//       // fluid_player_join(player);
////    if (fluid_file_renderer_process_block(renderer) != FLUID_OK)
////    {
////        break;
//    }
//
// if (typee == 4){
//    printf("playing");
//        fluid_player_set_loop(player,5);
//      //  fluid_player_join(player);
//      //  fluid_player_add(player,param);
//        fluid_player_play(player);
////if (fluid_player_get_status(player) == FLUID_PLAYER_PLAYING)
////{
////    if (fluid_file_renderer_process_block(renderer) != FLUID_OK)
////    {
////        break;
////    }
////}
//}
//
//else if (typee == 6){ // render audio to file.
////  if (fast_render) {
////    char *filename;
////    if (player == NULL) {
////      fprintf(stderr, "No midi file specified!\n");
////      goto cleanup;
////    }
////
////    fluid_settings_dupstr (settings, "audio.file.name", &filename);
////    printf ("Rendering audio to file '%s'..\n", filename);
////    if (filename) FLUID_FREE (filename);
////
////    fast_render_loop(settings, synth, player);
////  }
//}
//
//
//
//else if (typee == 5){
//#ifdef NETWORK_SUPPORTs
//  if (server != NULL) {
//    /* if the user typed 'quit' in the shell, kill the server */
//    if (!interactive) {
//      fluid_server_join(server);
//    }
//    delete_fluid_server(server);
//  }
//#endif
//
//  if (cmd_handler != NULL) {
//    delete_fluid_cmd_handler(cmd_handler);
//  }
//
//  if (player != NULL) {
//
//      fluid_player_stop(player);
//   // }
////    if (adriver != NULL || !fluid_settings_str_equal(settings, "player.timing-source", "sample")) {
////      /* if no audio driver and sample timers are used, nothing makes the player advance */
////      fluid_player_join(player);
////    }
//    delete_fluid_player(player);
//  }
//
//  if (router) {
//#if WITH_MIDI
//    if (mdriver) {
//      delete_fluid_midi_driver(mdriver);
//    }
//    delete_fluid_midi_router(router);
//#endif
//  }
//
//  /*if (sequencer) {
//    delete_fluid_sequencer(sequencer);
//  }*/
//
//  if (adriver) {
//    delete_fluid_audio_driver(adriver);
//  }
//
//  if (synth) {
//    delete_fluid_synth(synth);
//  }
//
//  if (settings) {
//    delete_fluid_settings(settings);
//  }
//}
//
////fluid_settings_setstr(settings, "audio.file.name", "/path/to/output.wav");
//

return Py_BuildValue("");
}
