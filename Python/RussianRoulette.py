"""
Based on buckshot roulette by Mike Klubnika
By: Hugo Nogueira 09/01/2024
The focus is to create a text-based game against a odds algorithm where the player and the algorithm play a russian roulette with items to aid make the game more interesting
"""
import random , time
runs = 0
def main() -> None:
    global name , playerLives , AILives, running
    running = True
    name = input("Welcome, insert your name:")
    print(f"Hello, {name} let's begin")
    time.sleep(1)
    print("Since you are new here I will let you pick how many times I can help you, but know I will also have the same amount of chances:")
    playerLives = int(input())
    if playerLives <= 0 or playerLives >= 11:
        print("Since you can't be reasonable, I will pick...")
        time.sleep(5)
        print("I will help you twice after that you are done")
        playerLives = 3
    AILives = playerLives
    print(f"So you will have {playerLives} lives")
    print("The weapon will have a random amount of bullets loaded, right now there is only 1 real and 1 blank")
    time.sleep(1.5)
    print("You can either shoot yourself or shoot me, if you shoot yourself with a blank you get to shoot again")
    time.sleep(3)
    print("Enough talk, let's begin...")
    time.sleep(1)
    bullets = [True, False]
    random.shuffle(bullets)
    turn = get_Input(bullets)
    if turn:
        turn = get_Input(bullets)
    else:
        turn = AIShoot(bullets ,bullets.pop(0) , [])
    Game(turn)
    


"""
Checks if the bullet is live or blank and determines if you get shot or not, return True means you get to shoot again, return False means you pass your turn --> works for the player
"""
def PlayerShoot(bullet , target , playerActives = [] , aiActives = []) -> bool:
    global playerLives , AILives , running
    if target == "player":
        print("---You aim at yourself and press the trigger---")
        time.sleep(3)
        if bullet == False:
            print("It was a blank, you have the next shot")
            return True
        else:
            shotThePlayer(playerActives)
            return False
    elif target == "ai":
        print("---You aim forward and press the trigger---")
        time.sleep(3)
        if bullet == False:
            print("It was a blank")
            return False
        else:
            shotTheAi(aiActives)
            return False
"""
Loop that runs while neither the player nor the "AI" dies. In the beginning of every round it reveals how many real bullets and blanks there are
"""
def Game(turn) -> None:
    playerActives = []
    aiActives = []
    global running
    print("From now on I will add one item to your inventory every round")
    items = {"reverse" : 0, "kevlar" : 0 , "pop" : 0}
    AIitems = {"reverse" : 0, "kevlar" : 0 , "pop" : 0}
    while running:
        bullets, items , AIitems= Reload(items ,AIitems, playerActives , aiActives)
        print(f"There are {bullets.count(True)} real bullets and {bullets.count(False)} blanks")
        print(f"You now have {items}")
        time.sleep(1)
        if turn:
            print("Go ahead and take the shot")
        else:
            print("Now I start")
        while len(bullets) != 0:
            if turn:
                turn = get_Input(bullets , items, playerActives)
            else:
                turn = AIShoot(bullets , bullets.pop(0), AIitems , playerActives)

"""
This function increments the amount of bullets by one while also making sure that there is always 1 live and 1 blank otherwise there would be cases where it would be a free round
"""
def Reload(items ,AIitems , playerActives , aiActives) -> list[bool]:
    global runs 
    if "kevlar" in playerActives:
        playerActives.pop(playerActives.index("kevlar"))
    if "kevlar" in aiActives:
        aiActives.pop(aiActives.index("kevlar"))
    bullets = []
    possibleItems = ["reverse", "kevlar" , "pop"]
    runs +=1
    item1 = possibleItems[random.randint(0, len(possibleItems)-1)]
    item2 = possibleItems[random.randint(0, len(possibleItems)-1)]
    items[item1] += 1
    AIitems[item2] += 1
    blanks = [False for x in range(random.randint(1, runs+1))]
    realBullets = [True for x in range(runs + 2 -len(blanks))]
    bullets = blanks + realBullets
    random.shuffle(bullets)
    return (bullets , items , AIitems)
"""
This function gets the user's input and filters it to the correct function after:
"""

def get_Input(bullets , items = {} , playerActives = []) -> bool:
    if len(bullets) > 0:    
        print('Input "Me" to shoot yourself, "You" to shoot me and "Items" to access the items menu')
        userInput = str(input())
        if userInput.upper() == "ME":
            turn = PlayerShoot(bullets.pop(0) , "player" , playerActives)
        elif userInput.upper() == "YOU":
            turn = PlayerShoot(bullets.pop(0) , "ai" , playerActives)
        elif userInput.upper() == "ITEMS":
            turn = item_Options(bullets , items, playerActives)
        else:
            turn = get_Input(bullets , items , playerActives)
        return turn
    else:
        return True
    
#Ideia é os items serem um dicionário em q a key é o nome do item e o valor associado é o número de uses que tens se for 0 , erro, senão baixa 1 
def item_Options(bullets , items, playerActives):
    print("You have the following items")
    print(items)
    playerInput = input("Input 1 to use them, 2 to get information about them or 3 to go back:")
    if playerInput == "1":
        itemPicked = input("Pick what item you wish to use:")
        if itemPicked in items.keys():
            if items[itemPicked] >= 1:
                items[itemPicked] -= 1
                if itemPicked == "reverse":
                    bullets[0] = reverse_bullet(bullets[0])
                    return get_Input(bullets, items , playerActives)
                if itemPicked == "kevlar":
                    kevlar("player" , playerActives)
                    return get_Input(bullets , items, playerActives)
                if itemPicked == "pop":
                    popBullet(items, "player" , bullets)
                    return get_Input(bullets , items , playerActives)
            elif itemPicked == "insert":
                bullets = insertBullet(items, "player" , bullets)
                return get_Input(bullets , items , playerActives)
            else:
                print("You don't have that item at your disposal")
                return get_Input(bullets, items , playerActives)
        else:
            print("Choose one of the available items")
            return item_Options(bullets , items, playerActives)
    elif playerInput == "2":
        itemPicked = input("Please indicate the name of the item you want to learn more about:")
        if itemPicked in items.keys():
            if itemPicked == "reverse":
                reverse_bullet(bullets[0] , True)
                return get_Input(bullets, items, playerActives)
            if itemPicked == "kevlar":
                kevlar("player" , playerActives , [] , True)
            if itemPicked == "pop":
                popBullet(items, "player" , bullets ,True)
            if itemPicked == "insert":
                insertBullet(items, "player",bullets , True)
        else:
            print("Choose one of the existing items")
            return item_Options(bullets, items , playerActives)
    elif playerInput == "3":
        return get_Input(bullets , items, playerActives)
    else:
        print("Choose one of the available options")
        return item_Options(bullets , items , playerActives)


"""
Function that tries to simulate simple AI: it sees how many bullets there are and calculates the best odds and plays using that information
Here since the system associates True with player's turn and False with AI's turn we swap what we did with the PlayerShoot() function
"""
def AIShoot(bullets , bullet , AIitems = dict(), playerActives = [], aiActives = []) -> bool:
    global playerLives , AILives , running
    print("---My turn---")
    time.sleep(2)
    bullets.append(bullet)
    blanks = bullets.count(False)
    real = bullets.count(True)
    if blanks == 0:
        if random.randint(1,2) == 1 and AIitems.get("reverse") > 0:
            target = "ai"
            print("I choose to shoot myself")
            bullet = reverse_bullet(bullet)
        else:
            target = "player"
    elif real == 0:
        if random.randint(1,2) == 1 and AIitems.get("reverse") > 0:
            target = "player"
            print("I choose to shoot you")
            bullet = reverse_bullet(bullet)
        else:
            target = "ai"
            print("I choose to shoot myself")
    else:
        favorableOdds = round(real / (blanks + real) , 2)
        if favorableOdds >= 0.5:
            target = "player"
            print("I choose to shoot you")
        else:
            print("I choose to shoot myself")
            target = "ai"
    bullets.pop(len(bullets)-1)
    if blanks + real >= 3 and AIitems["kevlar"] > 0:
        kevlar("ai")
    if target == "player":
        if bullet == True:
            shotThePlayer(playerActives)
            return True
        else:
            print("It was a blank!")
            return True
    else:
        if bullet == False:
            print("I was right! It was a blank")
            return False
        else:
            shotTheAi(aiActives)
            return True
        
def shotThePlayer(playerActives = []):
    global playerLives , running
    if "kevlar" not in playerActives:
        playerLives -= 1
        if playerLives == 0:
            running = False
            return dead()
        elif playerLives == 1:
            print(f"You got shot, I would be carefull you only have 1 more chance")
        else:
            print(f"You got shot, you now have {playerLives} chances left")
    else:
        print("The kevlar you had on saved you from the shot")
        playerActives.pop(playerActives.index("kevlar"))

def shotTheAi(aiActives = []):
    global AILives, running
    if "kevlar" not in aiActives:
        AILives -= 1
        if AILives == 0:
            running = False
            return win()
        elif AILives == 1:
            print(f"I got shot, this is my last chance please have mercy")
        else:
            print(f"I got shot but it's fine I still have {AILives} tries")
    else:
        print("I had a kevlar on so I'm fine")
        aiActives.pop(aiActives.index("kevlar"))

"""
Functions that end the game:
"""
def win():
    print("Congratulations! You win! but at what cost?")
    exit()

def dead():
    print("As expected, you are dead! Feel free to try again, if you think you can do better...")
    exit()

#From now on this functions are gonna be powers
    
"""
Reverse bullet: The objective is to allow the player or the "ai" to reverse the bullet, for example, if they know the bullet is a blank they can turn it into a live bullet or vice-versa
"""
def reverse_bullet(bullet , info = False) -> bool:
    if not info:
        print("The bullet has been reversed")
        if bullet and not info:                    #Implicit if bullet == True and info == False:
            return False
        elif not info:                        
            return True
    else:
        print("Using this item will cause the next bullet in the chamber to be the opposite of what it originally was.")
        print("If a bullet was a blank it would become real and vice-versa")    

"""
Kevlar: Allows the player to shield for the next turn without the "ai" knowing so and vice-versa
"""
def kevlar(caller , playerActives = [] , aiActives = [] , info = False):
    if info:
        print("This item will shield you for the next real shot")
    else:
        if caller == "player":
            if "kevlar" not in playerActives:
                playerActives.append("kevlar")
                print("You are protected for the next shot")
            else:
                print("You can only have 1 kevlar active at a time")
        else:
            if "kevlar" not in aiActives:
                aiActives.append("kevlar")
def popBullet(items,caller,bullets, info = False):
    if info:
        print("This item will remove the bullet in the chamber, allowing you to keep it and insert it later")
    else:
        if caller == "player":
            if "insert" not in items.keys():
                bullet = bullets.pop(0)
                items.update({"insert" : bullet})
                if bullet == True:
                    print("It was a real bullet")
                else:
                    print("It was a blank")
            else:
                print("You can only store a bullet at a time")
        else:
            """
            if "insert" not in #create AI items function:
                bullet = bullets.pop(0)
                #need to create an AIitems variable to store the aiITEMS 
            """
def insertBullet(items , caller , bullets , info = False): 
    if not info:
        if caller == "player":
            if items["insert"] == True:
                bullets.append(True)
                items.pop("insert")
                print("You added a real bullet")
            elif items["insert"] == False:
                bullets.append(False)
                print("You added a blank")
            else:
                print("You don't have a spare bullet")
                return bullets
            items.pop("insert")
            random.shuffle(bullets)
            return bullets
        # if caller == "AI":
        #     if True in aiActives:
        #         bullets.append(True)
        #         aiActives.pop(aiActives.index(True))
        #         print("I added a real bullet")
        #     elif False in aiActives:
        #         bullets.append(False)
        #         aiActives.pop(aiActives.index(False))
        #         print("I added a blank")
        #     else:
        #         return bullets
        #     return random.shuffle(bullets)
    else:
        print("The bullet you removed with the pop items is available to insert into the mag at a random spot")

main()
