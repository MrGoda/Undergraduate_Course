(defun playGame ()
"This is the start of game. First use shuffle function to return a deck with randomized sequence, use dealAll function deal first 26 cards from this deck to player, the other 26 to computerThe start of gameplay"
(write '"Game Begins!")
(terpri)
(terpri)
(cond ((< (dealAll (shuffle (list (list 2 'spades) (list 3 'spades) (list 4 'spades) (list 5 'spades) (list 6 'spades) (list 7 'spades) (list 8 'spades) (list 9 'spades) (list 10 'spades) (list 11 'spades) (list 12 'spades) (list 13 'spades) (list 14 'spades) (list 2 'hearts) (list 3 'hearts) (list 4 'hearts) (list 5 'hearts) (list 6 'hearts) (list 7 'hearts) (list 8 'hearts) (list 9 'hearts) (list 10 'hearts) (list 11 'hearts) (list 12 'hearts) (list 13 'hearts) (list 14 'hearts) (list 2 'clubs) (list 3 'clubs) (list 4 'clubs) (list 5 'clubs) (list 6 'clubs) (list 7 'clubs) (list 8 'clubs) (list 9 'clubs) (list 10 'clubs) (list 11 'clubs) (list 12 'clubs) (list 13 'clubs) (list 14 'clubs) (list 2 'diamonds) (list 3 'diamonds) (list 4 'diamonds) (list 5 'diamonds) (list 6 'diamonds) (list 7 'diamonds) (list 8 'diamonds) (list 9 'diamonds) (list 10 'diamonds) (list 11 'diamonds) (list 12 'diamonds) (list 13 'diamonds) (list 14 'diamonds)) 0)) 0)
       (return-from playGame 'playerLost))
      (t (return-from playGame 'playerWin))))



(defun shuffle (myDeck n)
"Shuffle myDeck, returns a randomized list"
(modifyAtIndex myDeck (random (- 52 n)) n))



(defun modifyAtIndex(Deck randomIndex n)
"Modify list at index"
(cond ((< n 51) 
       (cons (elt Deck randomIndex) (shuffle (remove (elt Deck randomIndex) Deck) (+ n 1))))
      ((= n 51)
       (return-from modifyAtIndex Deck))))



(defun dealAll (myDeck)
"Deal all by using dealPlayer and dealComputer function, eventually start the game"
(compare (dealPlayer myDeck 0) (dealComputer myDeck 26)))



(defun dealPlayer (myDeck n)
"Deal cards to player from first 26 cards in myDeck"
(cond ((< n (- (/ (length myDeck) 2) 1))
       (cons (elt myDeck n) (dealPlayer myDeck (+ 1 n))))
      ((= n (- (/ (length myDeck) 2) 1))
       (list (elt myDeck n)))))



(defun dealComputer (myDeck n)
"Deal cards to computer from last 26 cards in myDeck"
(cond ((< n (- (length myDeck) 1))
       (cons (elt myDeck n) (dealComputer myDeck (+ 1 n))))
      ((= n (- (length myDeck) 1))
       (list (elt myDeck n)))))



(defun getFirst (anyDeck)
"return the first element in anyDeck"
(car anyDeck))



(defun compare (playerDeck computerDeck)
"compare the first element of this two lists and determine which one have the larger numnber (or war)"

(cond ((= (ifWin playerDeck computerDeck) 1)
       (return-from compare 1))
      ((= (ifWin playerDeck computerDeck) -1)
       (return-from compare -1))
      ((= (ifWin playerDeck computerDeck) 0)
;this means that playerFirstCard is smaller
       (write '" Your card: ")
       (if (= (car (car playerDeck)) 14)
           (write (list 'Ace (car (cdr (car playerDeck)))))
         (write (car playerDeck)))
       (terpri)

       (write '"Bob plays: ")
       (if (= (car (car computerDeck)) 14)
           (write (list 'Ace (car (cdr (car computerDeck)))))
         (write (car computerDeck)))
       (terpri)

       (cond ((< (car (car playerDeck)) (car (car computerDeck)))
              (write '"Bob's card is bigger. He gets your card!")
              (terpri)
              (terpri)
              (compare (lose playerDeck) (win computerDeck playerDeck)))
;this means that playerFirstCard is bigger
             ((> (car (car playerDeck)) (car (car computerDeck)))
              (write '"Your card is bigger. You takes both cards!")
              (terpri)
              (terpri)
               (compare (win playerDeck computerDeck) (lose computerDeck)))
;this means that we go to war
             ((= (car (car playerDeck)) (car (car computerDeck)))
              (write '"Bob and you have the same number, let's go war!")
              (terpri)
              (terpri)
              (war playerDeck computerDeck))))))



(defun war (playerDeck computerDeck)

"In the case of war"
(cond ((= (ifWinForWar playerDeck computerDeck) 1)
       (return-from war 1))
      ((= (ifWinForWar playerDeck computerDeck) -1)
       (return-from war -1))
      ((= (ifWinForWar playerDeck computerDeck) 0)
       
       (write '" Your fifth card is: ")
        (if (= (car (elt playerDeck 4)) 14)
            (write (list 'Ace (car (cdr (elt playerDeck 4)))))
        (write (elt playerDeck 4)))
        (terpri)

        (write '" Bob's fifth card is: ")
        (if (= (car (elt computerDeck 4)) 14)
            (write (list 'Ace (car (cdr (elt computerDeck 4)))))
        (write (elt computerDeck 4)))
        (terpri)

        (cond ((< (car (elt playerDeck 4)) (car (elt computerDeck 4)))
               (write '"Bob Wins the war and takes all five of your cards!")
               (terpri)
               (terpri)
              (compare (lose (lose (lose (lose (lose playerDeck))))) (win (win (win (win (win computerDeck playerDeck) playerDeck) playerDeck) playerDeck) playerDeck)))
             ((> (car (elt playerDeck 4)) (car (elt computerDeck 4)))
              (write '"You Win the war and takes all five Bob's cards!")
              (terpri)
              (terpri)
              (compare (win (win (win (win (win playerDeck computerDeck) computerDeck) computerDeck) computerDeck) computerDeck) (lose (lose (lose (lose (lose computerDeck)))))))
             ((= (car (elt playerDeck 4)) (car (elt computerDeck 4)))
              (write '"Neither of you two win the war, we need another round!")
              (terpri)
              (terpri)
              (war (attachedToEnd (attachedToEnd (attachedToEnd (attachedToEnd (attachedToEnd playerDeck))))) (attachedToEnd (attachedToEnd (attachedToEnd (attachedToEnd (attachedToEnd computerDeck)))))))))))



(defun win (winDeck loseDeck)
"operation to winning deck, without any operation on losing deck"
(if (< (length loseDeck) 2)
    (if (< (length winDeck) 2)
        (cons loseDeck winDeck)
      (reverse (cons (car winDeck) (cons loseDeck (reverse (cdr winDeck))))))
  (reverse (cons (car winDeck) (cons (car loseDeck) (reverse (cdr winDeck)))))))



(defun lose (loseDeck)
"operation to losing deck, takes out the first element"
(if (< (length loseDeck) 2)
    (return-from lose loseDeck)
  (cdr loseDeck)))



(defun ifWin (playerDeck computerDeck)
"test if anyone wins"
(if (< (length playerDeck) 1)
     (return-from ifWin -1)
  (if (< (length computerDeck) 1)
      (return-from ifWin 1)
     (return-from ifWin 0))))



(defun ifWinForWar (playerDeck computerDeck)
"test if anyone wins when taking a war"
(if (< (length playerDeck) 5)
    (return-from ifWinForWar -1)
  (if (< (length computerDeck) 5)
      (return-from ifWinForWar 1)
    (return-from ifWinForWar 0))))



(defun attachedToEnd (anyDeck)
"let first element of anyDeck attach to the end of itself"
(if (< (length anyDeck) 2)
    (anyDeck)
(reverse (cons (car anyDeck) (reverse (cdr anyDeck))))))