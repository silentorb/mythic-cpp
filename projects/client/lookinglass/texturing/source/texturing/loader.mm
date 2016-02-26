#include "loader.h"
#include <UIKit/UIKit.h>

namespace texturing {

  unsigned char *load_png(const char *filename, int &width, int &height) {
    UIImage * image = [UIImage imageNamed:[NSString stringWithUTF8String:filename]];
    NSData * data = UIImagePNGRepresentation(image);
    return (unsigned char *) [data bytes];
  }
}
