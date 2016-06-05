//
// video::IImage* captcha = device->getVideoDriver()->createImage(video::ECF_A8R8G8B8,core::dimension2d<u32>(152,37));
// texture = device->getVideoDriver()->addTexture("CAPTCHA", captcha);
// packet >> (int*)texture->lock();
// texture->unlock();
// captcha->drop();
//
//
//
//if (!captcha) return;
// packetOut.appendArray((int*)captcha->lock(),captcha->getDimension().getArea());
// packetOut.compressPacket();
//   netManager->sendOutPacket(packetOut,playerId);
//    captcha->drop();
//
//
//    packetOut.appendArray(   << make your own
//
//
//
//
//
//Code:
//
//define SEND_FILE 0x20
//
//
//define ACK 0x47
//
//
//
//struct fileinfo
// {
//     char filename[MAXPATH];
//     unsigned long filesize;
//     unsigned long crc;
// } info;
//
//
//char data[513];
//int packs, remain,read;
//
//
//openfile(&(info.filename), &(info.file_size), &(info.crc)); //this function doesn't exist, is supposed to open the file, get its size, and calc the crc
//
//
//memset(data, 0, 256);
//
//
//*memset=SEND_FILE;
//memcpy(data+1,&info,sizeof(info));
//
//
//send(socket,data,256);
//recv(socket,data,256);
//if(*data!=ACK)
//   ;//transfer error
//
//
//remain=info.filesize % 512 ;
//packs=(info.filesize-ramain)/512;
//
//
//while(packs--)
//   {
//        if(!ReadFile(file,data,512,&read,NULL))
//            ; //read error
//        if(written!=pack)
//            ; //read error
//        send(socket,data,512);
//        recv(socket,data,256);
//        if(*data!=ACK)
//           ;//transfer error
//    }
//    if(!ReadFile(file,data,remain,&read,NULL))
//       ; //read error
//    if(written!=pack)
//       ; //read error
//
//
//    send(socket,data,remain);
//    recv(socket,data,256);
//    if(*data!=ACK)
//       ;//transfer error
//   }
//
//
//
//
//receiver:
//Code:
//
//define SEND_FILE 0x20
//
//
//define ACK 0x47
//
//
//
//struct fileinfo
// {
//     char filename[MAXPATH];
//     unsigned long filesize;
//     unsigned long crc;
// } info;
//
//
//char data[513];
//int packs, remain,written;
//
//
//open_file(); //this function doesn't exist, is supposed to get a filename, and open it for writing
//
//
//memset(data, 0, 256);
//
//
//recv(socket,data,256)
//if(data==SEND_FILE)
//   {
//       memcopy(&info,data+1,sizeof(info));
//       data=ACK;
//       send(socket,data,256);
//
//
//       remain=info.filesize % 512 ;
//       packs=(info.filesize-ramain)/512;
//
//
//
//       while(packs--)
//          {
//              recv(socket,data,512);
//              if(!WriteFile(file,data,512,&written,NULL))
//                 ; //write error
//              if(written!=pack)
//                 ; //write error
//              *data=ACK;
//              send(socket,data,256);
//          }
//        recv(socket,data,remain);
//        if(!WriteFile(file,data,remain,&written,NULL))
//            ; //write error
//        if(written!=pack)
//            ; //write error
//        *data=ACK;
//        send(socket,data,256);
//
//
//        if(calc_crc(file)!=info.crc)
//           ; //transfeer error
//
//   }
//
//
//I hope this work. I didn't test it. ACK and SEND_FILE aren't standards
//The crc is highly recomended
//
//
//good luck
