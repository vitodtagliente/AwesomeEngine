#include "components.h"

namespace component
{
const TypeDescriptor& Body2d::get_descriptor() const
{
    return Body2dType::descriptor();
}

fields_t Body2d::get_fields() const
{
    return Body2dType::fields(this);
}

void Body2d::autoload()
{
    TypeFactory::load<Body2d>();
}

const TypeDescriptor& Body2d::descriptor()
{
    return Body2dType::descriptor();
}

TypeDescriptor Body2dType::s_typeDescriptor{ Body2dType::registerTypeDescriptor };

const TypeDescriptor& Body2dType::descriptor()
{
    return s_typeDescriptor;
}

fields_t Body2dType::fields(const Body2d* const pointer)
{
    return fields_t();
}

void Body2dType::registerTypeDescriptor(TypeDescriptor* descriptor)
{
    descriptor->name = "Body2d";
    descriptor->size = sizeof(Body2d);
    descriptor->attributes.insert(std::make_pair<std::string, std::string>("Category", "Component"));

    TypeFactoryRegister::hook("Body2d", []() -> const TypeDescriptor& { return Body2dType::s_typeDescriptor; }, []() -> void* { return new Body2d(); });
}

const TypeDescriptor& Camera::get_descriptor() const
{
    return CameraType::descriptor();
}

fields_t Camera::get_fields() const
{
    return CameraType::fields(this);
}

void Camera::autoload()
{
    TypeFactory::load<Camera>();
}

const TypeDescriptor& Camera::descriptor()
{
    return CameraType::descriptor();
}

TypeDescriptor CameraType::s_typeDescriptor{ CameraType::registerTypeDescriptor };

const TypeDescriptor& CameraType::descriptor()
{
    return s_typeDescriptor;
}

fields_t CameraType::fields(const Camera* const pointer)
{
    return fields_t();
}

void CameraType::registerTypeDescriptor(TypeDescriptor* descriptor)
{
    descriptor->name = "Camera";
    descriptor->size = sizeof(Camera);
    descriptor->attributes.insert(std::make_pair<std::string, std::string>("Category", "Component"));

    TypeFactoryRegister::hook("Camera", []() -> const TypeDescriptor& { return CameraType::s_typeDescriptor; }, []() -> void* { return new Camera(); });
}

const TypeDescriptor& CameraController2d::get_descriptor() const
{
    return CameraController2dType::descriptor();
}

fields_t CameraController2d::get_fields() const
{
    return CameraController2dType::fields(this);
}

void CameraController2d::autoload()
{
    TypeFactory::load<CameraController2d>();
}

const TypeDescriptor& CameraController2d::descriptor()
{
    return CameraController2dType::descriptor();
}

TypeDescriptor CameraController2dType::s_typeDescriptor{ CameraController2dType::registerTypeDescriptor };

const TypeDescriptor& CameraController2dType::descriptor()
{
    return s_typeDescriptor;
}

fields_t CameraController2dType::fields(const CameraController2d* const pointer)
{
    return fields_t();
}

void CameraController2dType::registerTypeDescriptor(TypeDescriptor* descriptor)
{
    descriptor->name = "CameraController2d";
    descriptor->size = sizeof(CameraController2d);
    descriptor->attributes.insert(std::make_pair<std::string, std::string>("Category", "Component"));

    TypeFactoryRegister::hook("CameraController2d", []() -> const TypeDescriptor& { return CameraController2dType::s_typeDescriptor; }, []() -> void* { return new CameraController2d(); });
}

const TypeDescriptor& Collider2d::get_descriptor() const
{
    return Collider2dType::descriptor();
}

fields_t Collider2d::get_fields() const
{
    return Collider2dType::fields(this);
}

void Collider2d::autoload()
{
    TypeFactory::load<Collider2d>();
}

const TypeDescriptor& Collider2d::descriptor()
{
    return Collider2dType::descriptor();
}

TypeDescriptor Collider2dType::s_typeDescriptor{ Collider2dType::registerTypeDescriptor };

const TypeDescriptor& Collider2dType::descriptor()
{
    return s_typeDescriptor;
}

fields_t Collider2dType::fields(const Collider2d* const pointer)
{
    return fields_t();
}

void Collider2dType::registerTypeDescriptor(TypeDescriptor* descriptor)
{
    descriptor->name = "Collider2d";
    descriptor->size = sizeof(Collider2d);
    descriptor->attributes.insert(std::make_pair<std::string, std::string>("Category", "Component"));

    TypeFactoryRegister::hook("Collider2d", []() -> const TypeDescriptor& { return Collider2dType::s_typeDescriptor; }, []() -> void* { return new Collider2d(); });
}

const TypeDescriptor& GizmosRenderer::get_descriptor() const
{
    return GizmosRendererType::descriptor();
}

fields_t GizmosRenderer::get_fields() const
{
    return GizmosRendererType::fields(this);
}

void GizmosRenderer::autoload()
{
    TypeFactory::load<GizmosRenderer>();
}

const TypeDescriptor& GizmosRenderer::descriptor()
{
    return GizmosRendererType::descriptor();
}

TypeDescriptor GizmosRendererType::s_typeDescriptor{ GizmosRendererType::registerTypeDescriptor };

const TypeDescriptor& GizmosRendererType::descriptor()
{
    return s_typeDescriptor;
}

fields_t GizmosRendererType::fields(const GizmosRenderer* const pointer)
{
    return fields_t();
}

void GizmosRendererType::registerTypeDescriptor(TypeDescriptor* descriptor)
{
    descriptor->name = "GizmosRenderer";
    descriptor->size = sizeof(GizmosRenderer);
    descriptor->attributes.insert(std::make_pair<std::string, std::string>("Category", "Component"));

    TypeFactoryRegister::hook("GizmosRenderer", []() -> const TypeDescriptor& { return GizmosRendererType::s_typeDescriptor; }, []() -> void* { return new GizmosRenderer(); });
}

const TypeDescriptor& OrthographicCamera::get_descriptor() const
{
    return OrthographicCameraType::descriptor();
}

fields_t OrthographicCamera::get_fields() const
{
    return OrthographicCameraType::fields(this);
}

void OrthographicCamera::autoload()
{
    TypeFactory::load<OrthographicCamera>();
}

const TypeDescriptor& OrthographicCamera::descriptor()
{
    return OrthographicCameraType::descriptor();
}

TypeDescriptor OrthographicCameraType::s_typeDescriptor{ OrthographicCameraType::registerTypeDescriptor };

const TypeDescriptor& OrthographicCameraType::descriptor()
{
    return s_typeDescriptor;
}

fields_t OrthographicCameraType::fields(const OrthographicCamera* const pointer)
{
    return fields_t();
}

void OrthographicCameraType::registerTypeDescriptor(TypeDescriptor* descriptor)
{
    descriptor->name = "OrthographicCamera";
    descriptor->size = sizeof(OrthographicCamera);
    descriptor->attributes.insert(std::make_pair<std::string, std::string>("Category", "Component"));

    TypeFactoryRegister::hook("OrthographicCamera", []() -> const TypeDescriptor& { return OrthographicCameraType::s_typeDescriptor; }, []() -> void* { return new OrthographicCamera(); });
}

const TypeDescriptor& Particles2d::get_descriptor() const
{
    return Particles2dType::descriptor();
}

fields_t Particles2d::get_fields() const
{
    return Particles2dType::fields(this);
}

void Particles2d::autoload()
{
    TypeFactory::load<Particles2d>();
}

const TypeDescriptor& Particles2d::descriptor()
{
    return Particles2dType::descriptor();
}

TypeDescriptor Particles2dType::s_typeDescriptor{ Particles2dType::registerTypeDescriptor };

const TypeDescriptor& Particles2dType::descriptor()
{
    return s_typeDescriptor;
}

fields_t Particles2dType::fields(const Particles2d* const pointer)
{
    return fields_t();
}

void Particles2dType::registerTypeDescriptor(TypeDescriptor* descriptor)
{
    descriptor->name = "Particles2d";
    descriptor->size = sizeof(Particles2d);
    descriptor->attributes.insert(std::make_pair<std::string, std::string>("Category", "Component"));

    TypeFactoryRegister::hook("Particles2d", []() -> const TypeDescriptor& { return Particles2dType::s_typeDescriptor; }, []() -> void* { return new Particles2d(); });
}

const TypeDescriptor& SpriteAnimator::get_descriptor() const
{
    return SpriteAnimatorType::descriptor();
}

fields_t SpriteAnimator::get_fields() const
{
    return SpriteAnimatorType::fields(this);
}

void SpriteAnimator::autoload()
{
    TypeFactory::load<SpriteAnimator>();
}

const TypeDescriptor& SpriteAnimator::descriptor()
{
    return SpriteAnimatorType::descriptor();
}

TypeDescriptor SpriteAnimatorType::s_typeDescriptor{ SpriteAnimatorType::registerTypeDescriptor };

const TypeDescriptor& SpriteAnimatorType::descriptor()
{
    return s_typeDescriptor;
}

fields_t SpriteAnimatorType::fields(const SpriteAnimator* const pointer)
{
    return fields_t();
}

void SpriteAnimatorType::registerTypeDescriptor(TypeDescriptor* descriptor)
{
    descriptor->name = "SpriteAnimator";
    descriptor->size = sizeof(SpriteAnimator);
    descriptor->attributes.insert(std::make_pair<std::string, std::string>("Category", "Component"));

    TypeFactoryRegister::hook("SpriteAnimator", []() -> const TypeDescriptor& { return SpriteAnimatorType::s_typeDescriptor; }, []() -> void* { return new SpriteAnimator(); });
}

const TypeDescriptor& SpriteRenderer::get_descriptor() const
{
    return SpriteRendererType::descriptor();
}

fields_t SpriteRenderer::get_fields() const
{
    return SpriteRendererType::fields(this);
}

void SpriteRenderer::autoload()
{
    TypeFactory::load<SpriteRenderer>();
}

const TypeDescriptor& SpriteRenderer::descriptor()
{
    return SpriteRendererType::descriptor();
}

TypeDescriptor SpriteRendererType::s_typeDescriptor{ SpriteRendererType::registerTypeDescriptor };

const TypeDescriptor& SpriteRendererType::descriptor()
{
    return s_typeDescriptor;
}

fields_t SpriteRendererType::fields(const SpriteRenderer* const pointer)
{
    return fields_t();
}

void SpriteRendererType::registerTypeDescriptor(TypeDescriptor* descriptor)
{
    descriptor->name = "SpriteRenderer";
    descriptor->size = sizeof(SpriteRenderer);
    descriptor->attributes.insert(std::make_pair<std::string, std::string>("Category", "Component"));

    TypeFactoryRegister::hook("SpriteRenderer", []() -> const TypeDescriptor& { return SpriteRendererType::s_typeDescriptor; }, []() -> void* { return new SpriteRenderer(); });
}

} // namespace component
