#include "include/Btree.h"
#include "GameStatus.h"
#include "../../../Parameter/include/Parameter.h"
GameinfoDef gameinfo;
class BGameTime : public ConditionNode
{
public:
    BGameTime(const std::string &name, const NodeConfiguration &config) : ConditionNode(name, config)
    {
    }

    NodeStatus tick() override
    {

        if (gameinfo.RemainTime >= 360)
        {
            gameinfo.index = 1;
            gameinfo.Mtime = 0;
            return NodeStatus::SUCCESS;
        }
        return NodeStatus::FAILURE;
    }
    static PortsList providedPorts()
    {
        return {OutputPort<>("CarMessage")};
    }
};

class MGameTime : public ConditionNode
{
public:
    MGameTime(const std::string &name, const NodeConfiguration &config) : ConditionNode(name, config)
    {
    }

    NodeStatus tick() override
    {
        if (gameinfo.RemainTime >= 180 && gameinfo.RemainTime <= 360)
        {
            gameinfo.index = 2;
            gameinfo.Mtime = 0;
            return NodeStatus::SUCCESS;
        }
        return NodeStatus::FAILURE;
    }
    static PortsList providedPorts()
    {
        return {OutputPort<>("CarMessage")};
    }
};

class EGameTime : public ConditionNode
{
public:
    EGameTime(const std::string &name, const NodeConfiguration &config) : ConditionNode(name, config)
    {
    }

    NodeStatus tick() override
    {
        if (gameinfo.RemainTime >= 0 && gameinfo.RemainTime <= 180)
        {
            gameinfo.index = 3;
            gameinfo.Mtime = 0;
            return NodeStatus::SUCCESS;
        }
        return NodeStatus::FAILURE;
    }
    static PortsList providedPorts()
    {
        return {OutputPort<>("CarMessage")};
    }
};

class _359GameTime : public ConditionNode
{
public:
    _359GameTime(const std::string &name, const NodeConfiguration &config) : ConditionNode(name, config)
    {
    }

    NodeStatus tick() override
    {
        if (gameinfo.RemainTime <= 290 && gameinfo.RemainTime >= 200)
        {
            if (gameinfo.RemainTime <= 290 && gameinfo.RemainTime >= 280)
            {
                gameinfo.index = 5;
                return NodeStatus::SUCCESS;
            }
            else if (gameinfo.RemainTime <= 245 && gameinfo.RemainTime >= 230)
            {
                gameinfo.Mtime = 1;
                return NodeStatus::SUCCESS;
            }
        }
        return NodeStatus::FAILURE;
    }
    static PortsList providedPorts()
    {
        return {OutputPort<>("CarMessage")};
    }
};

class _645GameTime : public ConditionNode
{
public:
    _645GameTime(const std::string &name, const NodeConfiguration &config) : ConditionNode(name, config)
    {
    }

    NodeStatus tick() override
    {
        if (gameinfo.RemainTime >= 400 && gameinfo.RemainTime <= 415)
        {
            gameinfo.index = 4;
            gameinfo.Mtime = 1;

            return NodeStatus::SUCCESS;
        }
        return NodeStatus::FAILURE;
    }
    static PortsList providedPorts()
    {
        return {OutputPort<>("CarMessage")};
    }
};

class Missile : public ConditionNode
{
public:
    Missile(const std::string &name, const NodeConfiguration &config) : ConditionNode(name, config)
    {
    }

    NodeStatus tick() override
    {

        return NodeStatus::FAILURE;
    }
    static PortsList providedPorts()
    {
        return {OutputPort<>("CarMessage")};
    }
};

class Invasion : public ConditionNode
{
public:
    Invasion(const std::string &name, const NodeConfiguration &config) : ConditionNode(name, config)
    {
    }

    NodeStatus tick() override
    {
        static int count;
        if (count == 40)
            count = 0;
        if (gameinfo.inInvasion == true && count <= 20)
        {
            gameinfo.index = 7;
            count++;
            return NodeStatus::SUCCESS;
        }
        count++;
        return NodeStatus::FAILURE;
    }
    static PortsList providedPorts()
    {
        return {OutputPort<>("CarMessage")};
    }
};

class HP : public ConditionNode
{
public:
    HP(const std::string &name, const NodeConfiguration &config) : ConditionNode(name, config)
    {
    }

    NodeStatus tick() override
    {
        static int count;
        if (gameinfo.recover == 1)
        {
            count = 0;
            gameinfo.recover = 0;
        }
        if (gameinfo.RobotHP == 1 && count <= 20)
        {
            gameinfo.index = 8;
            count++;
            return NodeStatus::SUCCESS;
        }
        return NodeStatus::FAILURE;
    }
    static PortsList providedPorts()
    {
        return {OutputPort<>("CarMessage")};
    }
};

class SHP : public ConditionNode
{
public:
    SHP(const std::string &name, const NodeConfiguration &config) : ConditionNode(name, config)
    {
    }

    NodeStatus tick() override
    {
        static int count;
        if (gameinfo.SHP <= 300 && count <= 20)
        {
            gameinfo.index = 9;
            count++;
            return NodeStatus::SUCCESS;
        }
        return NodeStatus::FAILURE;
    }
    static PortsList providedPorts()
    {
        return {OutputPort<>("CarMessage")};
    }
};

class FHP : public ConditionNode
{
public:
    FHP(const std::string &name, const NodeConfiguration &config) : ConditionNode(name, config)
    {
    }

    NodeStatus tick() override
    {
        /* static int count;
        if (gameinfo.FHP <= 800 && count <= 20)
        {

            //gameinfo.index = 10;
            count++;
            return NodeStatus::SUCCESS;
        } */
        return NodeStatus::FAILURE;
    }
    static PortsList providedPorts()
    {
        return {OutputPort<>("CarMessage")};
    }
};

class AHP : public ConditionNode
{
public:
    AHP(const std::string &name, const NodeConfiguration &config) : ConditionNode(name, config)
    {
    }

    NodeStatus tick() override
    {
        /*  static int count;
        if (gameinfo.arecover == 1)
        {
            count = 0;
            gameinfo.arecover = 0;
        }
        if (gameinfo.AHP == 1 && count <= 20)
        {
            gameinfo.index = 11;
            count++;
            return NodeStatus::SUCCESS;
        } */
        return NodeStatus::FAILURE;
    }
    static PortsList providedPorts()
    {
        return {OutputPort<>("CarMessage")};
    }
};

class Buff : public ConditionNode
{
public:
    Buff(const std::string &name, const NodeConfiguration &config) : ConditionNode(name, config)
    {
    }

    NodeStatus tick() override
    {
        if (gameinfo.BuffAvailable)
        {
            gameinfo.index = 12;
            return NodeStatus::SUCCESS;
        }
        return NodeStatus::FAILURE;
    }
    static PortsList providedPorts()
    {
        return {OutputPort<>("CarMessage")};
    }
};

class IsRoad : public ConditionNode
{
public:
    IsRoad(const std::string &name, const NodeConfiguration &config) : ConditionNode(name, config)
    {
    }

    NodeStatus tick() override
    {
        static int count;
        if (count == 40)
            count = 0;
        if (gameinfo.isRoad == true && count <= 20)
        {
            gameinfo.index = 13;
            count++;
            return NodeStatus::SUCCESS;
        }
        count++;
        return NodeStatus::FAILURE;
    }
    static PortsList providedPorts()
    {
        return {OutputPort<>("CarMessage")};
    }
};

class SendToOtherRobot : public SyncActionNode
{
public:
    SendToOtherRobot(const std::string &name, const NodeConfiguration &config) : SyncActionNode(name, config)
    {
    }

    NodeStatus tick() override
    {
        /* auto res = getInput<int>("CarMessage");
        if (!res)
        {
            throw RuntimeError("error reading port [target]:", res.error());
        } */
        gameinfo.showqueue.emplace_back(gameinfo.index);
        for (auto id : gameinfo.sendqueue)
        {
            if (gameinfo.index == id)
                return NodeStatus::SUCCESS;
        };
        //串口发消息
        messageselect();
        //gameinfo.judge->writeToReferee(gameinfo.judge->referee.robot_client_ID.hero);
        //gameinfo.judge->writeToReferee(gameinfo.judge->referee.robot_client_ID.engineer);
        //gameinfo.judge->writeToReferee(gameinfo.judge->referee.robot_client_ID.infantry_4);
        //gameinfo.judge->writeToReferee(gameinfo.judge->referee.robot_client_ID.infantry_5);
        if (gameinfo.index == 6 || gameinfo.index == 7 || gameinfo.index == 8)
            return NodeStatus::SUCCESS;
        gameinfo.sendqueue.emplace_back(gameinfo.index);
        //cout << "sent:" << gameinfo.index << '\n';
        return NodeStatus::SUCCESS;
    }

    static PortsList providedPorts()
    {
        // Optionally, a port can have a human readable description
        const char *description = "CarCommuniction...";
        return {InputPort<int>("CarMessage", description)};
    }
};

Tree init_BT(BehaviorTreeFactory &factory, refereeio &_judge)
{
    /* PortsList in_ports = {BT::InputPort<int>("CarMessage")};
    PortsList out_ports = {BT::OutputPort<int>("CarMessage")}; */
    factory.registerNodeType<SendToOtherRobot>("SendToOtherRobot");
    factory.registerNodeType<BGameTime>("BGameTime");
    factory.registerNodeType<MGameTime>("MGameTime");
    factory.registerNodeType<EGameTime>("EGameTime");
    factory.registerNodeType<_645GameTime>("_645GameTime");
    factory.registerNodeType<_359GameTime>("_359GameTime");
    factory.registerNodeType<HP>("HP");
    factory.registerNodeType<SHP>("SHP");
    factory.registerNodeType<AHP>("AHP");
    factory.registerNodeType<FHP>("FHP");
    factory.registerNodeType<Buff>("Buff");
    factory.registerNodeType<Missile>("Missile");
    factory.registerNodeType<Invasion>("Invasion");
    factory.registerNodeType<IsRoad>("IsRoad");
    gameinfo.sendToSentry = false;
    gameinfo.suggestion = 0x00;
    gameinfo.judge = &_judge;
    gameinfo.judge->_PackToSentry.PackToSentry.CarDensityMax = 0xff;
    gameinfo.judge->_PackToSentry.PackToSentry.carnum = 0xff;
    gameinfo.judge->_PackToSentry.PackToSentry.EnermyToDead = 0xff;
    gameinfo.judge->_PackToSentry.PackToSentry.isMissile = 0xff;
    gameinfo.judge->_PackToGroundRobotStrat.PackToGroundRobotStrat.protect = 0x00;
    gameinfo.judge->_PackToGroundRobotStrat.PackToGroundRobotStrat.attack = 0x00;
    gameinfo.judge->_PackToGroundRobotStrat.PackToGroundRobotStrat.event = 0x00;
    gameinfo.judge->_PackToHero.PackToHero.suggestion = 0x00;
    gameinfo.judge->_PackToInfantry.PackToInfantry.suggestion = 0x00;
    gameinfo.judge->_PackToEngineer.PackToEngineer.suggestion = 0x00;

    auto tree = factory.createTreeFromFile(param.btreefile);
    return tree;
}
