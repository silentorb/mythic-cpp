//
//  Gamepad_Manager.m
//  mythical
//
//  Created by Chris Johnson on 1/3/16.
//
//

#import "Gamepad_Manager.h"

@interface Gamepad_Manager() {
//    CBCentralManager* bluetooth;
}
@end

@implementation Gamepad_Manager

- (id)init
{
    self = [super init];
    if (self)
    {
//        bluetooth =  [[CBCentralManager alloc] initWithDelegate:self queue:nil options:nil];
//        [self update];
    }
    return self;
}

//- (void)centralManagerDidUpdateState:(CBCentralManager *)central {
//    
//}
//
//- (void)update{
//    [bluetooth scanForPeripheralsWithServices:nil options:nil];
//}
//
//- (void)centralManager:(CBCentralManager *)central didDiscoverPeripheral:(CBPeripheral *)peripheral advertisementData:(NSDictionary<NSString *,id> *)advertisementData RSSI:(NSNumber *)RSSI {
//    NSLog(@"Discovered %@", peripheral.name);
//}

@end
