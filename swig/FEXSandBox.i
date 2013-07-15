%module FEX

%feature("ref") SpriteComponent "nimei;$this->retain();"
%feature("unref") SpriteComponent "nimei;$this->release();"

class SpriteComponent 
{
};

