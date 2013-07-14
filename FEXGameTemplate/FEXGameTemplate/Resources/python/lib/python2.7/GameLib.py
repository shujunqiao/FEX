import FEX
import sys
controller_1 = None
hero = None
game = None



class GameDot(FEX.GameBase):
    def __init__(self):
        print "create GameDot: from python"
        FEX.GameBase.__init__(self)
        self.should_end = False
    def update(self, *args):
        FEX.GameBase.update(self, *args)
#        if ( self.should_end ):
#            print "end game"
#            self.clean()
#
#            self = None


class HeroController(FEX.IOSTouchController):
    def __init__(self):
        self.center = FEX.CCPoint(80,80)
        FEX.IOSTouchController.__init__(self)
        self.indicator = FEX.SpriteBase(self.center ,FEX.map_string_string({ "sprite_desc" : "saw"}) )
        self.indicator_ptr = make_shared_ptr(self.indicator)
        FEX.get_game().add_game_object( self.indicator_ptr, "root" )

    
    def ccTouchBegan(self, touch, event):
        cnt = hero.component_count()
        hero.component(0).apply_force( FEX.CCPoint(100,100) )
        
        game.clean()
        global controller_1
        controller_1 = None
        return True
    def ccTouchMoved(self, *args):
        print "touch moved"
        return

class Hero(FEX.SpriteBase):
    def __init__(self, *args):
        FEX.SpriteBase.__init__(self, *args)

def make_shared_ptr( p ):
    p.__disown__()
    ret = FEX.make_gameobj_ptr(p)
    return ret


def run_game():
    print sys.path
    global game
    global controller_1
    global hero
    game = GameDot()
    game.__disown__()
    FEX.set_game( game )

    hero = Hero(FEX.map_string_string(
                                  { "init_location":"500,500",
                                  "sprite_desc" : "saw"}))
    controller_1 = HeroController()
    controller_1.hero = hero
    game.add_game_object( make_shared_ptr(hero), "root" )
    FEX.get_game_info().add_controller(controller_1)
    controller_1.plug()

