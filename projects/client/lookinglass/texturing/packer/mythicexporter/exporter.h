#pragma once
// SmartUpdateHash: {{smartUpdateKey}}

#include "texturing/Image_Info.h"

extern texturing::Sprite_Sheet Sprite_Sheet_{{settings.tpsName}};
extern const texturing::Image_Info Image_Info_{{settings.tpsName}}[];

enum Images_{{settings.tpsName}} {{% for sprite in allSprites %}
  {{ sprite.trimmedName}}{% if not forloop.last %}, {% endif %}{% endfor %}
};
