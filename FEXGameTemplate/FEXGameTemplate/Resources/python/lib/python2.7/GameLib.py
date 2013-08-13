import FEX
import sys
controller_1 = None
hero = None
game = None


def create_sprite( x, y ):
    dot = Dot(FEX.CCPoint(x*60+200, y*60 + 100) )
    FEX.get_game().add_game_object( make_shared_ptr(dot), "root" )
    return dot

class Dot(FEX.SpriteBase):
    def __init__(self, point):
        FEX.SpriteBase.__init__( self, point ,FEX.map_string_string({ "sprite_desc" : "saw"}) )

class GameDot(FEX.GameBase):

    def __init__(self):
        print "create GameDot: from python"
        FEX.GameBase.__init__(self)
        FEX.set_game( self )
        self.should_end = False
        self.dots = []
        for i in range(0,8*8):
            self.dots.append(create_sprite(i%8, i/8))

    def get_dot( self, pt ):
        x = pt.x
        y = pt.y

        x-=200
        y-=100
        x = int(x/60)
        y = int(y/60)
        if ( x >= 0 and x < 8 and y >=0 and y < 8 ):
            return self.dots[x + y*8]
        return None
    
        
    
    def update(self, *args):
        FEX.GameBase.update(self, *args)

class HeroController(FEX.IOSTouchController):

    def __init__(self):
        FEX.IOSTouchController.__init__(self)

    
    def ccTouchBegan(self, touch, event):
        global game

        dot = game.get_dot( touch.getLocation() )
        if ( dot ):
            dot.selected()

        return True
    def ccTouchMoved(self, touch, event):
        dot = game.get_dot( touch.getLocation() )
        if ( dot ):
            dot.selected()
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


    controller_1 = HeroController()
    FEX.get_game_info().add_controller(controller_1)
    controller_1.plug()

