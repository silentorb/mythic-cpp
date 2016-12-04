#include "{{settings.tpsName}}.h"
#include "images.h"

texturing::Sprite_Sheet Sprite_Sheet_{{settings.tpsName}} = {
  nullptr, "{{texture.trimmedName}}", {{texture.size.width}}, {{texture.size.height}}
};

const texturing:: Image_Info Image_Info_{{settings.tpsName}}[] { {% for sprite in texture.allSprites %}
  { &Sprite_Sheet_{{settings.tpsName}}, "{{sprite.trimmedName}}", {{sprite.frameRect.x}}, {{sprite.frameRect.y}}, {{sprite.frameRect.width}}, {{sprite.frameRect.height}} }{% if not forloop.last %}, {% endif %}{% endfor %}
};
