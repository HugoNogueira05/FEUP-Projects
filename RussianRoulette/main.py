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
    if playerLives <= 0:
        print("Since you can't be reasonable, I will pick...")
        time.sleep(5)
        print("I will help you twice after that you are done")
        playerLives = 3
    AILives = playerLives
    print("The weapon will have a random amount of bullets loaded, right now there is only 1 real and 1 blank")
    time.sleep(1.5)
    print("You can either shoot yourself or shoot me, if you shoot yourself with a blank you get to shoot again")
    time.sleep(3)
    print("Enough talk, let's begin...")
    time.sleep(1)
    print('Input "me"/"Me" to shoot yourself or "you"/"You" to shoot me')
    bullets = [True, False]
    play = input()
    if play == "me" or play=="Me":
        playAgain = PlayerShoot(bullets.pop(random.randint(0, len(bullets)-1)) , "player")
    else:
        playAgain = PlayerShoot(bullets.pop(random.randint(0, len(bullets)-1)), "ai")
    if playAgain == True:
        play = input()
        if play == "me" or play=="Me":
            playAgain = PlayerShoot(bullets.pop(random.randint(0, len(bullets)-1)) , "player")
        else:
            playAgain = PlayerShoot(bullets.pop(random.randint(0, len(bullets)-1)), "ai")
    else:
        AIShoot(bullets , bullets.pop(random.randint(0, len(bullets)-1)))
    game()
    


"""
Checks if the bullet is live or blank and determines if you get shot or not, return True means you get to shoot again, return False means you pass your turn --> works for the player
"""
def PlayerShoot(bullet , target) -> bool:
    global playerLives , AILives , running
    if target ==  "player":
        print("---You aim at yourself and press the trigger---")
        time.sleep(3)
        if bullet == False:
            print("It was a blank, you have the next shot")
            return True
        else:
            playerLives -= 1
            if playerLives == 0:
                running = False
                return dead()
            elif playerLives == 1:
                print(f"You shot yourself, I would be carefull you only have 1 more chance")
            else:
                print(f"You shot yourself, you now have {playerLives} chances left")
            return False
    elif target == "ai":
        print("---You aim forward and press the trigger---")
        time.sleep(3)
        if bullet == False:
            print("It was a blank")
            return False
        else:
            AILives -= 1
            if AILives == 0:
                running = False
                return win()
            elif AILives == 1:
                print(f"You got me, this is my last chance please have mercy")
            else:
                print(f"You got it right but it's fine I still have {AILives} tries")
            return False
"""
Loop that runs while neither the player nor the "AI" dies in the beginning of every round it reveals how many lives and blanks there are
"""
def game() -> None:
    global running
    while running:
        bullets = reload()
        print(f"There are {bullets.count(True)} real bullets and {bullets.count(False)} blanks")
        time.sleep(1)
        print("Go ahead and take the shot")
        turn = True
        while len(bullets) != 0:
            if turn:
                play = input()
                if play == "me" or play == "Me":
                    turn = PlayerShoot(bullets.pop(random.randint(0, len(bullets)-1)) , "player")
                elif play == "you" or play== "You":
                    turn = PlayerShoot(bullets.pop(random.randint(0, len(bullets)-1)) , "ai")
                else:
                    raise Exception('Input can only be "You/you" or "Me/me"')
            else:
                turn = AIShoot(bullets , bullets.pop(random.randint(0, len(bullets)-1)))

"""
This function increments the amount of bullets by one while also making sure that there is always 1 live and 1 blank otherwise there would be cases where it would be a free round
"""
def reload() -> list[bool]:
    global runs
    bullets = []
    runs +=1
    blanks = [False for x in range(random.randint(1, runs+1))]
    realBullets = [True for x in range(runs + 2 -len(blanks))]
    bullets = blanks + realBullets
    return bullets

"""
Function that tries to simulate simple AI: it sees how many bullets there are and calculates the best odds and plays using that information
Here since the system associates True with player's turn and False with AI's turn we swap what we did with the PlayerShoot() function
"""
def AIShoot(bullets , bullet) -> bool:
    global playerLives , AILives , running
    print("---My turn---")
    time.sleep(2)
    bullets.append(bullet)
    blanks = bullets.count(False)
    real = bullets.count(True)
    if blanks == 0:
        target = "player"
        print("I choose to shoot you")
    elif real == 0:
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
    bullets.remove(bullet)
    if target == "player":
        if bullet == True:
            playerLives -= 1
            if playerLives == 0:
                running = False
                dead()
            elif playerLives == 1:
                print(f"Ha ha! Be carefull now you only have {playerLives} last try")
            else:
                print(f"Got you! Now you only have {playerLives} lives left")
                return True
        else:
            print("It was a blank!")
            return True
    else:
        if bullet == False:
            print("I was right! It was a blank")
            return False
        else:
            AILives -= 1
            if AILives == 0:
                running = False
                win()
            elif AILives == 1:
                print(f"Damn! I thought it was a blank! This is my last chance")
            else:
                print(f"Guess I was wrong, well I still have {AILives} tries")
            return True
"""
Functions that end the game:
"""
def win():
    print("Congratulations! You win! but at what cost?")
    exit()

def dead():
    print("As expected, you are dead! Feel free to try again, if you think you can do better...")
    exit()

main()