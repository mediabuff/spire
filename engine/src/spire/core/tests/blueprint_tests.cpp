////////////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2012 Robert Engeln (engeln@gmail.com)
//  See accompanying LICENSE file for full license information.
////////////////////////////////////////////////////////////////////////////////

#include "prefix.hpp"
#include "spire/common/property.hpp"
#include "spire/core/blueprint.hpp"
#include "spire/core/blueprint_service.hpp"
#include "spire/core/service.hpp"

using namespace spire;

namespace
{
    enum AnimalStatus
    {
        AnimalStatus_Wild,
        AnimalStatus_FoodSource,
        AnimalStatus_Pet,
        AnimalStatus_Intelligent
    };

    BEGIN_ENUM_LABELS(AnimalStatus)
        DEF_ENUM_LABEL("wild", AnimalStatus_Wild)
        DEF_ENUM_LABEL("foodSource", AnimalStatus_FoodSource)
        DEF_ENUM_LABEL("pet", AnimalStatus_Pet)
        DEF_ENUM_LABEL("intelligent", AnimalStatus_Intelligent)
    END_ENUM_LABELS()

    class AnimalBlueprint : public BlueprintInterface<class Animal>
    {
    public:
        std::string scientificName;
        AnimalStatus status;
        BEGIN_HOST_PROPERTY_MAP()
            DEF_PROPERTY(scientificName)
            DEF_PROPERTY(status)
        END_HOST_PROPERTY_MAP()
    };

    class Animal
    {
    public:
        std::string scientificName;
        AnimalStatus status;

        Animal(const class AnimalBlueprint& blueprint)
        : scientificName(blueprint.scientificName),
          status(blueprint.status)
        {
        }

        virtual ~Animal() = 0 { };
    };

    class BirdBlueprint : public BasicBlueprint<BirdBlueprint, Animal, AnimalBlueprint>
    {
    public:
        virtual std::unique_ptr<Animal> Construct() const;

        bool canFly;
        BEGIN_HOST_PROPERTY_MAP()
            INHERIT_PROPERTIES(AnimalBlueprint)
            DEF_PROPERTY(canFly)
        END_HOST_PROPERTY_MAP()
    };

    class Bird : public Animal
    {
    public:
        bool canFly;

        Bird(const class BirdBlueprint& blueprint)
        : Animal(blueprint), canFly(blueprint.canFly)
        {
        }
    };

    inline std::unique_ptr<Animal> BirdBlueprint::Construct() const
    {
        return std::unique_ptr<Animal>(new Bird(*this));
    }

    class MammalBlueprint : public BasicBlueprint<MammalBlueprint, Animal, AnimalBlueprint>
    {
    public:
        virtual std::unique_ptr<Animal> Construct() const;

        int legs;
        BEGIN_HOST_PROPERTY_MAP()
            INHERIT_PROPERTIES(AnimalBlueprint)
            DEF_PROPERTY(legs)
        END_HOST_PROPERTY_MAP()
    };

    class Mammal : public Animal
    {
    public:
        int legs;

        Mammal(const MammalBlueprint& blueprint)
        : Animal(blueprint), legs(blueprint.legs)
        {
        }
    };

    inline std::unique_ptr<Animal> MammalBlueprint::Construct() const
    {
        return std::unique_ptr<Animal>(new Mammal(*this));
    }
}

TEST(BlueprintTests, BlueprintsCanBeLoadedFromXml)
{
    auto svc = GetFramework().Acquire<BlueprintServiceFactory>("DefaultBlueprintService").Construct();
    svc->Register("mammal", std::unique_ptr<Blueprint>(new MammalBlueprint()));
    svc->Register("bird", std::unique_ptr<Blueprint>(new BirdBlueprint()));
    
    const char* xml =
        "<blueprints>\n"
        "   <mammal name=\"man\">\n"
        "       <scientificName>Homo sapien</scientificName>\n"
        "       <legs>2</legs>\n"
        "       <status>intelligent</status>"
        "   </mammal>\n"
        "   <mammal name=\"dog\">\n"
        "       <scientificName>Canis familiaris</scientificName>\n"
        "       <legs>4</legs>\n"
        "       <status>pet</status>"
        "   </mammal>\n"
        "   <bird name=\"raven\">\n"
        "       <scientificName>Corvus corax</scientificName>\n"
        "       <canFly>1</canFly>\n"
        "       <status>wild</status>\n"
        "   </bird>\n"
        "   <bird name=\"chicken\">\n"
        "       <scientificName>Gallus gallus domesticus</scientificName>\n"
        "       <canFly>0</canFly>\n"
        "       <status>foodSource</status>\n"
        "   </bird>\n"
        "</blueprints>\n";
    std::vector<char> buf(xml, xml + strlen(xml) + 1);
    svc->Parse(std::move(buf));

    auto man = svc->Acquire<Animal>("man").Construct();
    ASSERT_STREQ("Homo sapien", man->scientificName.c_str());
    ASSERT_EQ(2, dynamic_cast<Mammal*>(man.get())->legs);
    ASSERT_EQ(AnimalStatus_Intelligent, man->status);
    auto dog = svc->Acquire<Animal>("dog").Construct();
    ASSERT_STREQ("Canis familiaris", dog->scientificName.c_str());
    ASSERT_EQ(4, dynamic_cast<Mammal*>(dog.get())->legs);
    ASSERT_EQ(AnimalStatus_Pet, dog->status);
    auto raven = svc->Acquire<Animal>("raven").Construct();
    ASSERT_STREQ("Corvus corax", raven->scientificName.c_str());
    ASSERT_TRUE(dynamic_cast<Bird*>(raven.get())->canFly);
    ASSERT_EQ(AnimalStatus_Wild, raven->status);
    auto chicken = svc->Acquire<Animal>("chicken").Construct();
    ASSERT_STREQ("Gallus gallus domesticus", chicken->scientificName.c_str());
    ASSERT_FALSE(dynamic_cast<Bird*>(chicken.get())->canFly);
    ASSERT_EQ(AnimalStatus_FoodSource, chicken->status);
}
