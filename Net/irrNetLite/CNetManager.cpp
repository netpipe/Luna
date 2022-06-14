#include "CNetManager.h"
#include <iostream>

namespace irr
{
	namespace net
	{
		CNetManager::CNetManager(INetCallback* handler, u32 port, const SNetParams& params) :
			pHandler(handler), netIterations(10000), netParams(params), verbose(0),
			globPacketRelay(false), connectionStatus(EICS_PENDING)
		{
			if (enet_initialize() != 0)
				std::cout << "irrNetLite: An error occurred while initializing ENet.\n";

			connectionStatus = setUpServer(port) ? EICS_ESTABLISHED : EICS_FAILED;
		}

		CNetManager::CNetManager(INetCallback* handler, const c8* addressc,
			const u32 port, const SNetParams& params) :
			pHandler(handler), netIterations(10000), netParams(params), verbose(0),
			globPacketRelay(false), connectionStatus(EICS_PENDING)
		{
			if (enet_initialize() != 0)
				std::cout << "irrNetLite: An error occurred while initializing ENet.\n";

			if(!setUpClient(addressc, port))
				connectionStatus = EICS_FAILED;
		}

		CNetManager::~CNetManager(void)
		{
			if(host)
				enet_host_destroy(host);

			enet_deinitialize();
		}

		bool CNetManager::setUpClient(const c8* addressc, const u32 port)
		{
			mode = ENM_CLIENT;

			if(verbose)
				std::cout << "irrNetLite: Creating client!" << std::endl;

		//	host = enet_host_create(NULL, 1, 2,netParams.downBandwidth / 8, netParams.upBandwidth / 8);
			host = enet_host_create(NULL, 1, netParams.downBandwidth / 8, netParams.upBandwidth / 8);
			ENetEvent event;

			enet_address_set_host(&address, addressc);
			address.port = port;

			if(verbose)
				std::cout	<< "irrNetLite: Connecting to "
							<< addressc	<< ":" << port << std::endl;

			// Sets up two channels.
			//peer = enet_host_connect(host, &address, 2,2);
			peer = enet_host_connect(host, &address, 2);

			if(peer == NULL)
			{
				std::cout << "irrNetLite: Error: Could not resolve server address. Connection failed.\n";
				return false;
			}

			if(!(	enet_host_service(host, &event, netParams.connectionTimeout) > 0 &&
					event.type == ENET_EVENT_TYPE_CONNECT))
			{
				enet_peer_reset(peer);

				std::cout << "irrNetLite: Error: Connection timed out. Connection failed.\n";
				return false;
			}

			while(enet_host_service(host, &event, netParams.connectionTimeout) > 0)
			{
				if(event.channelID == 1 && event.type == ENET_EVENT_TYPE_RECEIVE)
				{
					enet_uint8* buff = event.packet->data;

					u8 packiden = 0;
					memcpy((char*)&packiden, buff, 1);

					if(packiden == 4)
					{
						memcpy((char*)&playerID, buff+1, 2);

						if(playerID == 0)
						{
							std::cout << "irrNetLite: Error: Null player ID recieved. Server likely full.";
							enet_peer_reset(event.peer);
							return false;
						}

						if(verbose)
							std::cout << "irrNetLite: Player ID is " << playerID << ".\n";

						u8 packid = 3;
						ENetPacket* packet = enet_packet_create(&packid, 1, ENET_PACKET_FLAG_RELIABLE);
						enet_host_broadcast(host, 1, packet);

						return true;
					}
				}
			}

			std::cout << "irrNetLite: Error: Failed to recieve Player ID. Connection failed.\n";
			return false;
		}

		bool CNetManager::setUpServer(const u32 port)
		{
			mode = ENM_SERVER;
			netParams.maxClients++;

			address.host = ENET_HOST_ANY;
			address.port = port;

			if(verbose)
				std::cout << "irrNetLite: Creating server!\n";

			//host = enet_host_create(&address, netParams.maxClients,1, 0,0);
			host = enet_host_create(&address, netParams.maxClients, 0,0);

			if(host == NULL)
			{
				std::cout << "irrNetLite: Error: An error occurred while trying to create an ENet server host.\n";
				return false;
			}

			players.resize(netParams.maxClients, 0);

			return true;
		}

		void CNetManager::setGlobalPacketRelay(bool relay)
		{
			globPacketRelay = relay;
		}

		void CNetManager::update(const u32 timeOut)
		{
			if(connectionStatus == EICS_FAILED)
				return;

			if(mode == ENM_CLIENT)
			{
				ENetEvent event;

				for(u32 i = 0; i < netIterations;i++)
				{
					if(!(enet_host_service(host, &event, i ? 1 : timeOut) > 0))
						break;

					switch (event.type)
					{
					case ENET_EVENT_TYPE_RECEIVE:
						{
							enet_uint8* buff = event.packet->data;

							if(event.channelID == 1)
							{
								u8 packiden = 0;
								memcpy((char*)&packiden,buff,1);

								if(packiden == 3)
								{
									connectionStatus = EICS_ESTABLISHED;
									if(pHandler) pHandler->onConnect(0);
								}
							}
							else
							{
								if(verbose)
									std::cout	<< "irrNetLite: A packet of length "
												<< event.packet->dataLength
												<< " was received.\n";

								SInPacket inpacket((c8*)buff, (u32)event.packet->dataLength);

								if(pHandler)
									pHandler->handlePacket(inpacket);
							}

							buff = 0;
							enet_packet_destroy(event.packet);
							break;
						}
					case ENET_EVENT_TYPE_DISCONNECT:
						std::cout << "irrNetLite: Connection to server lost.\n";

						event.peer->data = 0;
						connectionStatus = EICS_FAILED;

						if(pHandler)
							pHandler->onDisconnect(0);
					default:
						break;
					}
				}

			}
			else // (mode == ENM_SERVER)
			{
				ENetEvent event;

				for(u32 i = 0;i < netIterations;i++)
				{
					if(!(enet_host_service (host, &event, i ? 1 : timeOut) > 0))
						break;

					switch (event.type)
					{
					case ENET_EVENT_TYPE_CONNECT:
						{
							if(verbose)
								std::cout	<< "irrNetLite: A new client connected from "
											<< event.peer->address.host << ":"
											<< event.peer->address.port << std::endl;

							u16 pID = 1;

							while(pID < netParams.maxClients && players[pID] != 0)
								pID++;

							if(pID >= netParams.maxClients)
							{
								if(verbose)
									std::cout 	<< "irrNetLite: Warning: Client rejected. Too many clients."
												<< std::endl;

								pID = 0;
							}
							else
							{
								event.peer->data = players[pID] = new SPeerData(pID, event.peer);
							}

							c8 buffer[3];
							u8 packid = 4;
							memcpy(buffer, (char*)&packid, 1);
							memcpy(buffer+1, (char*)&pID, 2);
							ENetPacket* packet;
							packet = enet_packet_create(buffer, 3, ENET_PACKET_FLAG_RELIABLE);
							enet_peer_send(event.peer, 1, packet);
							enet_host_flush(host);

							if(pID == 0) enet_peer_reset(event.peer);

							break;
						}
					case ENET_EVENT_TYPE_RECEIVE:
						{
							enet_uint8* buff = event.packet->data;

							if(event.channelID == 1)
							{
								u8 packiden = 0;
								memcpy((char*)&packiden, buff, 1);

								if(packiden == 3)
								{
									ENetPacket* packet = enet_packet_create(&packiden, 1, ENET_PACKET_FLAG_RELIABLE);
									enet_peer_send(event.peer, 1, packet);
									SPeerData* currentPeer = reinterpret_cast<SPeerData*>(event.peer->data);
									if(currentPeer && pHandler) pHandler->onConnect(currentPeer->playerID);
								}
							}
							else
							{
								SPeerData* currentPeer = reinterpret_cast<SPeerData*>(event.peer->data);

								if(currentPeer)
								{
									SInPacket inPacket((c8*)buff, (u32)event.packet->dataLength);
									inPacket.setPlayerId(currentPeer->playerID);

									if(verbose)
										std::cout	<< "irrNetLite: A packet of length "
													<< event.packet->dataLength
													<< " from player number "
													<< currentPeer->playerID
													<< " was received.\n";

									if(pHandler)
										pHandler->handlePacket(inPacket);

									if(globPacketRelay)
									{
										SOutPacket relayPacket((c8*)buff, (u32)event.packet->dataLength);

										const u32 playersSize = (u32)players.size();
										for(u32 i = 0;i < playersSize;++i)
											if(players[i] && players[i] != currentPeer)
												sendOutPacket(relayPacket, i);
									}
								}
							}

							buff = 0;
							enet_packet_destroy(event.packet);
							break;
						}
					case ENET_EVENT_TYPE_DISCONNECT:
						{
							SPeerData* pData = reinterpret_cast<SPeerData*>(event.peer->data);

							if(pData)
							{
								if(verbose)
									std::cout	<< "irrNetLite: Player number "
												<< pData->playerID
												<< " disconnected.\n";

								if(pHandler) pHandler->onDisconnect(pData->playerID);

								players[pData->playerID] = 0;
								delete pData;
								event.peer->data = 0;
							}
						}
					default:
						break;
					}
				}
			}
		}

		void CNetManager::setVerbose(bool isverbose)
		{
			verbose = isverbose;
		}

		ENetPeer* CNetManager::getPlayerById(u16 id)
		{
			if(id < players.size() && players[id] && players[id]->playerID == id)
				return players[id]->enetPeer;

			return 0;
		}

		ENetPeer* CNetManager::getPeer()
		{
			if(connectionStatus == EICS_ESTABLISHED)
				return &host->peers[0];
			else
				return 0;
		}

		const u32 CNetManager::getPing()
		{
			if(getPeer())
				return getPeer()->roundTripTime;
			else
				return 0;
		}

		const u32 CNetManager::getPeerCount()
		{
			return (u32)host->peerCount;
		}

		const u16 CNetManager::getPlayerNumber()
		{
			return playerID;
		}

		ENetHost* CNetManager::getHost()
		{
			return host;
		}

		E_IRRNET_CONNECTION_STATUS CNetManager::getConnectionStatus()
		{
			return connectionStatus;
		}

		void CNetManager::kickClient(const u16 playerId, bool hardKick = false)
		{
			ENetPeer* currentPeer = getPlayerById(playerId);

	//		if(currentPeer)
//				hardKick ?	enet_peer_disconnect_now(currentPeer) :
	//						enet_peer_disconnect(currentPeer);
		}

		const u32 CNetManager::getClientAddress(const u16 playerId)
		{
			ENetPeer* currentPeer = getPlayerById(playerId);

			if(currentPeer)
				return currentPeer->address.host;

			return 0;
		}

		void CNetManager::sendOutPacket(SOutPacket& outpacket)
		{
			ENetPacket* packet = enet_packet_create((char*)outpacket.getData(), outpacket.getSize(),
				ENET_PACKET_FLAG_RELIABLE);

			enet_host_broadcast(host, 0, packet);
		}

		void CNetManager::sendOutPacket(SOutPacket& outpacket, const u16 playerId)
		{
			ENetPacket* packet = enet_packet_create ((char*)outpacket.getData(), outpacket.getSize(),
				ENET_PACKET_FLAG_RELIABLE);
			ENetPeer* currentPeer = getPlayerById(playerId);

			if(currentPeer && currentPeer->state == ENET_PEER_STATE_CONNECTED)
				enet_peer_send(currentPeer, 0, packet);
		}

		void CNetManager::sendOutPacketUnreliable(SOutPacket& outpacket)
		{
			ENetPacket* packet = enet_packet_create((char*)outpacket.getData(), outpacket.getSize(), 0);
			enet_host_broadcast(host, 0, packet);
		}

		void CNetManager::sendOutPacketUnreliable(SOutPacket& outpacket, const u16 playerId)
		{
			ENetPacket* packet = enet_packet_create((char*)outpacket.getData(), outpacket.getSize(), 0);
			ENetPeer* currentPeer = getPlayerById(playerId);

			if(currentPeer && currentPeer->state == ENET_PEER_STATE_CONNECTED)
				enet_peer_send(currentPeer, 0, packet);
		}

		extern INetManager* createIrrNetClient(INetCallback* callback, const c8* addressc, const u32 port, const SNetParams& params)
		{
			return new irr::net::CNetManager(callback, addressc, port, params);
		}
		extern INetManager* createIrrNetServer(INetCallback* callback, const u32 port, const SNetParams& params)
		{
			return new irr::net::CNetManager(callback, port, params);
		}

	} // Close Net Namespace
} // Close Irr namespace

// Copyright(C) Ahmed Hilali 2007

/* License:

This software is provided 'as-is', without any express or implied
warranty.  In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not
claim that you wrote the original software. If you use this software
in a product, an acknowledgement in the product documentation would be
appreciated but is not required.
2. Altered source versions must be clearly marked as such, and must not be
misrepresented as being the original software.
3. This notice may not be removed or altered from any source distribution.

*/
