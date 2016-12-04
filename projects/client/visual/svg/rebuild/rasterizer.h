#pragma once

namespace pugi {
	class xml_document;
}

unsigned char *data rasterize(pugi::xml_document & document, int &width, int &height);