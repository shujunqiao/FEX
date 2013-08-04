//
//  DataSources.m
//  Editor
//
//  Created by Fancyzero on 13-8-4.
//
//

#import "DataSources.h"
#import "FE.h"

@implementation SpriteClassDataSource
-(id) init
{
	self = [super init];
	sprite_classes = [NSMutableArray array];
    [sprite_classes retain];
	return self;
}
-(NSInteger) numberOfItemsInComboBox:(NSComboBox *)aComboBox
{
	if ( sprite_classes != nil )
		return [sprite_classes count];
	else
		return 0;
}


- (id)comboBox:(NSComboBox *)aComboBox objectValueForItemAtIndex:(NSInteger)index
{
	if ( sprite_classes == nil )
		return NULL;
	
	if (index > [sprite_classes count] || index < 0  )
		return nil;
	return [sprite_classes objectAtIndex:index ];
	
}

-(void) collect_classes
{
    [sprite_classes removeAllObjects];
    auto classes = FESimple::GameObjFactory::get_all_classes();
    for ( auto i : classes )
    {
        [sprite_classes addObject: [NSString stringWithUTF8String: i->name.c_str()]];
    }
}

@end

