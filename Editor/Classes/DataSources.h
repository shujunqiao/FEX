//
//  DataSources.h
//  Editor
//
//  Created by Fancyzero on 13-8-4.
//
//

#import <Foundation/Foundation.h>

@interface SpriteClassDataSource : NSObject<NSComboBoxDataSource>
{
@public
	NSMutableArray*	sprite_classes;
}

-(void) collect_classes;

@end
