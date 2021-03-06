#pragma once
#include <memory>

class MessageHandler;
class NetworkClient;
struct NetworkPacket;
namespace GameSocket
{
    class GameHandlers
    {
    public:
        static void Setup(MessageHandler*);
        static bool SMSG_CREATE_PLAYER(std::shared_ptr<NetworkClient>, NetworkPacket*);
        static bool SMSG_CREATE_ENTITY(std::shared_ptr<NetworkClient>, NetworkPacket*);
        static bool SMSG_UPDATE_ENTITY(std::shared_ptr<NetworkClient>, NetworkPacket*);
        static bool SMSG_DELETE_ENTITY(std::shared_ptr<NetworkClient>, NetworkPacket*);
    };
}