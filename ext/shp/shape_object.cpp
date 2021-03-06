
#include "shape_object.hpp"

namespace shp {

VALUE shape_object::_klass = Qnil;

VALUE shape_object::klass() {
  return shape_object::_klass;
}

shape_object::shape_object(SHPObject *handle)
  : _handle(handle)
{
}

shape_object::~shape_object() {
  if (_handle) {
    SHPDestroyObject(_handle);
    _handle = NULL;
  }
}

VALUE shape_object::compute_extents(VALUE self)
{
  shape_object *object = unwrap(self);

  CHECK_VALID_HANDLE(object->value());

  SHPComputeExtents(object->value());

  return object->wrapped();
}

VALUE shape_object::destroy(VALUE self)
{
  shape_object *object = unwrap(self);

  CHECK_VALID_HANDLE(object->value());

  if (object->value()) {
    SHPDestroyObject(object->value());
    object->_handle = NULL;
  }

  return Qnil;
}

VALUE shape_object::get_shape_type(VALUE self)
{
  shape_object *object = unwrap(self);

  CHECK_VALID_HANDLE(object->value());

  return INT2FIX(object->value()->nSHPType);
}

VALUE shape_object::get_shape_id(VALUE self)
{
  shape_object *object = unwrap(self);

  CHECK_VALID_HANDLE(object->value());

  return INT2FIX(object->value()->nShapeId);
}

VALUE shape_object::get_shape_parts(VALUE self)
{
  shape_object *object = unwrap(self);

  CHECK_VALID_HANDLE(object->value());

  return INT2FIX(object->value()->nParts);
}

VALUE shape_object::get_shape_part_starts(VALUE self)
{
  shape_object *object = unwrap(self);

  CHECK_VALID_HANDLE(object->value());

  VALUE result = rb_ary_new();

  SHPObject *obj = object->value();

  if (obj && obj->panPartStart) {
    for (int i = 0; i < obj->nParts; ++i) {
      rb_ary_push(result, INT2FIX(obj->panPartStart[i]));
    }
  }

  return result;
}

VALUE shape_object::get_shape_part_types(VALUE self)
{
  shape_object *object = unwrap(self);

  CHECK_VALID_HANDLE(object->value());

  VALUE result = rb_ary_new();

  SHPObject *obj = object->value();

  if (obj && obj->panPartType) {
    for (int i = 0; i < obj->nParts; ++i) {
      rb_ary_push(result, INT2FIX(obj->panPartType[i]));
    }
  }

  return result;
}

VALUE shape_object::get_vertex_count(VALUE self)
{
  shape_object *object = unwrap(self);

  CHECK_VALID_HANDLE(object->value());

  return INT2FIX(object->value()->nVertices);
}

VALUE shape_object::get_x(VALUE self)
{
  shape_object *object = unwrap(self);

  CHECK_VALID_HANDLE(object->value());

  VALUE result = rb_ary_new();

  SHPObject *obj = object->value();

  if (obj && obj->padfX) {
    for (int i = 0; i < obj->nVertices; ++i) {
      rb_ary_push(result, rb_float_new(obj->padfX[i]));
    }
  }

  return result;
}

VALUE shape_object::get_y(VALUE self)
{
  shape_object *object = unwrap(self);

  CHECK_VALID_HANDLE(object->value());

  VALUE result = rb_ary_new();

  SHPObject *obj = object->value();

  if (obj && obj->padfY) {
    for (int i = 0; i < obj->nVertices; ++i) {
      rb_ary_push(result, rb_float_new(obj->padfY[i]));
    }
  }

  return result;
}

VALUE shape_object::get_z(VALUE self)
{
  shape_object *object = unwrap(self);

  CHECK_VALID_HANDLE(object->value());

  VALUE result = rb_ary_new();

  SHPObject *obj = object->value();

  if (obj && obj->padfZ) {
    for (int i = 0; i < obj->nVertices; ++i) {
      rb_ary_push(result, rb_float_new(obj->padfZ[i]));
    }
  }

  return result;
}

VALUE shape_object::get_m(VALUE self)
{
  shape_object *object = unwrap(self);

  CHECK_VALID_HANDLE(object->value());

  VALUE result = rb_ary_new();

  SHPObject *obj = object->value();

  if (obj && obj->padfM) {
    for (int i = 0; i < obj->nVertices; ++i) {
      rb_ary_push(result, rb_float_new(obj->padfM[i]));
    }
  }

  return result;
}

VALUE shape_object::get_x_min(VALUE self)
{
  shape_object *object = unwrap(self);

  CHECK_VALID_HANDLE(object->value());

  return rb_float_new(object->value()->dfXMin);
}

VALUE shape_object::get_y_min(VALUE self)
{
  shape_object *object = unwrap(self);

  CHECK_VALID_HANDLE(object->value());

  return rb_float_new(object->value()->dfYMin);
}

VALUE shape_object::get_z_min(VALUE self)
{
  shape_object *object = unwrap(self);

  CHECK_VALID_HANDLE(object->value());

  return rb_float_new(object->value()->dfZMin);
}

VALUE shape_object::get_m_min(VALUE self)
{
  shape_object *object = unwrap(self);

  CHECK_VALID_HANDLE(object->value());

  return rb_float_new(object->value()->dfMMin);
}

VALUE shape_object::get_x_max(VALUE self)
{
  shape_object *object = unwrap(self);

  CHECK_VALID_HANDLE(object->value());

  return rb_float_new(object->value()->dfXMax);
}

VALUE shape_object::get_y_max(VALUE self)
{
  shape_object *object = unwrap(self);

  CHECK_VALID_HANDLE(object->value());

  return rb_float_new(object->value()->dfYMax);
}

VALUE shape_object::get_z_max(VALUE self)
{
  shape_object *object = unwrap(self);

  CHECK_VALID_HANDLE(object->value());

  return rb_float_new(object->value()->dfZMax);
}

VALUE shape_object::get_m_max(VALUE self)
{
  shape_object *object = unwrap(self);

  CHECK_VALID_HANDLE(object->value());

  return rb_float_new(object->value()->dfMMax);
}

void shape_object::define(VALUE module)
{
  shape_object::_klass = rb_define_class_under(module, "ShapeObject", rb_cObject);
  base<shape_object>::define(shape_object::_klass, false);
  rb_define_method(shape_object::_klass, "compute_extents", SHP_METHOD(shape_object::compute_extents), 0);
  rb_define_method(shape_object::_klass, "get_shape_type", SHP_METHOD(shape_object::get_shape_type), 0);
  rb_define_method(shape_object::_klass, "get_shape_id", SHP_METHOD(shape_object::get_shape_id), 0);
  rb_define_method(shape_object::_klass, "get_shape_parts", SHP_METHOD(shape_object::get_shape_parts), 0);
  rb_define_method(shape_object::_klass, "get_shape_part_starts", SHP_METHOD(shape_object::get_shape_part_starts), 0);
  rb_define_method(shape_object::_klass, "get_shape_part_types", SHP_METHOD(shape_object::get_shape_part_types), 0);
  rb_define_method(shape_object::_klass, "get_vertex_count", SHP_METHOD(shape_object::get_vertex_count), 0);
  rb_define_method(shape_object::_klass, "get_x", SHP_METHOD(shape_object::get_x), 0);
  rb_define_method(shape_object::_klass, "get_y", SHP_METHOD(shape_object::get_y), 0);
  rb_define_method(shape_object::_klass, "get_z", SHP_METHOD(shape_object::get_z), 0);
  rb_define_method(shape_object::_klass, "get_m", SHP_METHOD(shape_object::get_m), 0);
  rb_define_method(shape_object::_klass, "get_x_min", SHP_METHOD(shape_object::get_x_min), 0);
  rb_define_method(shape_object::_klass, "get_y_min", SHP_METHOD(shape_object::get_y_min), 0);
  rb_define_method(shape_object::_klass, "get_z_min", SHP_METHOD(shape_object::get_z_min), 0);
  rb_define_method(shape_object::_klass, "get_m_min", SHP_METHOD(shape_object::get_m_min), 0);
  rb_define_method(shape_object::_klass, "get_x_max", SHP_METHOD(shape_object::get_x_max), 0);
  rb_define_method(shape_object::_klass, "get_y_max", SHP_METHOD(shape_object::get_y_max), 0);
  rb_define_method(shape_object::_klass, "get_z_max", SHP_METHOD(shape_object::get_z_max), 0);
  rb_define_method(shape_object::_klass, "get_m_max", SHP_METHOD(shape_object::get_m_max), 0);
  rb_define_method(shape_object::_klass, "destroy", SHP_METHOD(shape_object::destroy), 0);
}

}

