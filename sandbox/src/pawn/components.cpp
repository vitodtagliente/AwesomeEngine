#include "components.h"

const TypeDescriptor& Bullet::get_descriptor() const
{
    return BulletType::descriptor();
}

fields_t Bullet::get_fields() const
{
    return BulletType::fields(this);
}

void Bullet::autoload()
{
    TypeFactory::load<Bullet>();
}

const TypeDescriptor& Bullet::descriptor()
{
    return BulletType::descriptor();
}

TypeDescriptor BulletType::s_typeDescriptor{ BulletType::registerTypeDescriptor };

const TypeDescriptor& BulletType::descriptor()
{
    return s_typeDescriptor;
}

fields_t BulletType::fields(const Bullet* const)
{
    return fields_t();
}

void BulletType::registerTypeDescriptor(TypeDescriptor* descriptor)
{
    descriptor->name = "Bullet";
    descriptor->size = sizeof(Bullet);
    descriptor->attributes.insert(std::make_pair<std::string, std::string>("Category", "Component"));

    TypeFactoryRegister::hook("Bullet", []() -> const TypeDescriptor& { return BulletType::s_typeDescriptor; }, []() -> void* { return new Bullet(); });
}

const TypeDescriptor& CameraFollow2d::get_descriptor() const
{
    return CameraFollow2dType::descriptor();
}

fields_t CameraFollow2d::get_fields() const
{
    return CameraFollow2dType::fields(this);
}

void CameraFollow2d::autoload()
{
    TypeFactory::load<CameraFollow2d>();
}

const TypeDescriptor& CameraFollow2d::descriptor()
{
    return CameraFollow2dType::descriptor();
}

TypeDescriptor CameraFollow2dType::s_typeDescriptor{ CameraFollow2dType::registerTypeDescriptor };

const TypeDescriptor& CameraFollow2dType::descriptor()
{
    return s_typeDescriptor;
}

fields_t CameraFollow2dType::fields(const CameraFollow2d* const)
{
    return fields_t();
}

void CameraFollow2dType::registerTypeDescriptor(TypeDescriptor* descriptor)
{
    descriptor->name = "CameraFollow2d";
    descriptor->size = sizeof(CameraFollow2d);
    descriptor->attributes.insert(std::make_pair<std::string, std::string>("Category", "Component"));

    TypeFactoryRegister::hook("CameraFollow2d", []() -> const TypeDescriptor& { return CameraFollow2dType::s_typeDescriptor; }, []() -> void* { return new CameraFollow2d(); });
}

const TypeDescriptor& CombatController::get_descriptor() const
{
    return CombatControllerType::descriptor();
}

fields_t CombatController::get_fields() const
{
    return CombatControllerType::fields(this);
}

void CombatController::autoload()
{
    TypeFactory::load<CombatController>();
}

const TypeDescriptor& CombatController::descriptor()
{
    return CombatControllerType::descriptor();
}

TypeDescriptor CombatControllerType::s_typeDescriptor{ CombatControllerType::registerTypeDescriptor };

const TypeDescriptor& CombatControllerType::descriptor()
{
    return s_typeDescriptor;
}

fields_t CombatControllerType::fields(const CombatController* const)
{
    return fields_t();
}

void CombatControllerType::registerTypeDescriptor(TypeDescriptor* descriptor)
{
    descriptor->name = "CombatController";
    descriptor->size = sizeof(CombatController);
    descriptor->attributes.insert(std::make_pair<std::string, std::string>("Category", "Component"));

    TypeFactoryRegister::hook("CombatController", []() -> const TypeDescriptor& { return CombatControllerType::s_typeDescriptor; }, []() -> void* { return new CombatController(); });
}

const TypeDescriptor& Crosshair::get_descriptor() const
{
    return CrosshairType::descriptor();
}

fields_t Crosshair::get_fields() const
{
    return CrosshairType::fields(this);
}

void Crosshair::autoload()
{
    TypeFactory::load<Crosshair>();
}

const TypeDescriptor& Crosshair::descriptor()
{
    return CrosshairType::descriptor();
}

TypeDescriptor CrosshairType::s_typeDescriptor{ CrosshairType::registerTypeDescriptor };

const TypeDescriptor& CrosshairType::descriptor()
{
    return s_typeDescriptor;
}

fields_t CrosshairType::fields(const Crosshair* const)
{
    return fields_t();
}

void CrosshairType::registerTypeDescriptor(TypeDescriptor* descriptor)
{
    descriptor->name = "Crosshair";
    descriptor->size = sizeof(Crosshair);
    descriptor->attributes.insert(std::make_pair<std::string, std::string>("Category", "Component"));

    TypeFactoryRegister::hook("Crosshair", []() -> const TypeDescriptor& { return CrosshairType::s_typeDescriptor; }, []() -> void* { return new Crosshair(); });
}

const TypeDescriptor& Health::get_descriptor() const
{
    return HealthType::descriptor();
}

fields_t Health::get_fields() const
{
    return HealthType::fields(this);
}

void Health::autoload()
{
    TypeFactory::load<Health>();
}

const TypeDescriptor& Health::descriptor()
{
    return HealthType::descriptor();
}

TypeDescriptor HealthType::s_typeDescriptor{ HealthType::registerTypeDescriptor };

const TypeDescriptor& HealthType::descriptor()
{
    return s_typeDescriptor;
}

fields_t HealthType::fields(const Health* const)
{
    return fields_t();
}

void HealthType::registerTypeDescriptor(TypeDescriptor* descriptor)
{
    descriptor->name = "Health";
    descriptor->size = sizeof(Health);
    descriptor->attributes.insert(std::make_pair<std::string, std::string>("Category", "Component"));

    TypeFactoryRegister::hook("Health", []() -> const TypeDescriptor& { return HealthType::s_typeDescriptor; }, []() -> void* { return new Health(); });
}

const TypeDescriptor& Lifetime::get_descriptor() const
{
    return LifetimeType::descriptor();
}

fields_t Lifetime::get_fields() const
{
    return LifetimeType::fields(this);
}

void Lifetime::autoload()
{
    TypeFactory::load<Lifetime>();
}

const TypeDescriptor& Lifetime::descriptor()
{
    return LifetimeType::descriptor();
}

TypeDescriptor LifetimeType::s_typeDescriptor{ LifetimeType::registerTypeDescriptor };

const TypeDescriptor& LifetimeType::descriptor()
{
    return s_typeDescriptor;
}

fields_t LifetimeType::fields(const Lifetime* const)
{
    return fields_t();
}

void LifetimeType::registerTypeDescriptor(TypeDescriptor* descriptor)
{
    descriptor->name = "Lifetime";
    descriptor->size = sizeof(Lifetime);
    descriptor->attributes.insert(std::make_pair<std::string, std::string>("Category", "Component"));

    TypeFactoryRegister::hook("Lifetime", []() -> const TypeDescriptor& { return LifetimeType::s_typeDescriptor; }, []() -> void* { return new Lifetime(); });
}

const TypeDescriptor& Pawn::get_descriptor() const
{
    return PawnType::descriptor();
}

fields_t Pawn::get_fields() const
{
    return PawnType::fields(this);
}

void Pawn::autoload()
{
    TypeFactory::load<Pawn>();
}

const TypeDescriptor& Pawn::descriptor()
{
    return PawnType::descriptor();
}

TypeDescriptor PawnType::s_typeDescriptor{ PawnType::registerTypeDescriptor };

const TypeDescriptor& PawnType::descriptor()
{
    return s_typeDescriptor;
}

fields_t PawnType::fields(const Pawn* const)
{
    return fields_t();
}

void PawnType::registerTypeDescriptor(TypeDescriptor* descriptor)
{
    descriptor->name = "Pawn";
    descriptor->size = sizeof(Pawn);
    descriptor->attributes.insert(std::make_pair<std::string, std::string>("Category", "Component"));

    TypeFactoryRegister::hook("Pawn", []() -> const TypeDescriptor& { return PawnType::s_typeDescriptor; }, []() -> void* { return new Pawn(); });
}

const TypeDescriptor& PawnController::get_descriptor() const
{
    return PawnControllerType::descriptor();
}

fields_t PawnController::get_fields() const
{
    return PawnControllerType::fields(this);
}

void PawnController::autoload()
{
    TypeFactory::load<PawnController>();
}

const TypeDescriptor& PawnController::descriptor()
{
    return PawnControllerType::descriptor();
}

TypeDescriptor PawnControllerType::s_typeDescriptor{ PawnControllerType::registerTypeDescriptor };

const TypeDescriptor& PawnControllerType::descriptor()
{
    return s_typeDescriptor;
}

fields_t PawnControllerType::fields(const PawnController* const)
{
    return fields_t();
}

void PawnControllerType::registerTypeDescriptor(TypeDescriptor* descriptor)
{
    descriptor->name = "PawnController";
    descriptor->size = sizeof(PawnController);
    descriptor->attributes.insert(std::make_pair<std::string, std::string>("Category", "Component"));

    TypeFactoryRegister::hook("PawnController", []() -> const TypeDescriptor& { return PawnControllerType::s_typeDescriptor; }, []() -> void* { return new PawnController(); });
}

const TypeDescriptor& Rotator::get_descriptor() const
{
    return RotatorType::descriptor();
}

fields_t Rotator::get_fields() const
{
    return RotatorType::fields(this);
}

void Rotator::autoload()
{
    TypeFactory::load<Rotator>();
}

const TypeDescriptor& Rotator::descriptor()
{
    return RotatorType::descriptor();
}

TypeDescriptor RotatorType::s_typeDescriptor{ RotatorType::registerTypeDescriptor };

const TypeDescriptor& RotatorType::descriptor()
{
    return s_typeDescriptor;
}

fields_t RotatorType::fields(const Rotator* const)
{
    return fields_t();
}

void RotatorType::registerTypeDescriptor(TypeDescriptor* descriptor)
{
    descriptor->name = "Rotator";
    descriptor->size = sizeof(Rotator);
    descriptor->attributes.insert(std::make_pair<std::string, std::string>("Category", "Component"));

    TypeFactoryRegister::hook("Rotator", []() -> const TypeDescriptor& { return RotatorType::s_typeDescriptor; }, []() -> void* { return new Rotator(); });
}

