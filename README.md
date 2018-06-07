# HeartQuake
Simulates the HeartQuake game for a given number of cycles. Reports winners and ongoing games.

HeartQuake is the English translation for the name of traditional Italian game of cards, “strappacuore”. The game is played by two opponents with the forty cards of the “Neapolitan” pack. HeartQuake is actually a deterministic procedure: once a shuffling is distributed to the players, the outcome of the game is decided . Moreover, its rules are so simple that it can be played by children. Though the playing of the game is simple, it is quite difficult for an external watcher to foresee the outcome of the game at any moment because of the ease with which the fates of the game rapidly change. This is probably the main reason for the name and the fortune of this game.

The traditional game HeartQuake is based on the 40 playing cards in the Neapolitan pack of cards. Two players are involved, let’s call them Neal and Jack. After a shuffling, 20 cards are given to Neal, 20 to Jack. All cards are unknown to both. A table is available to put cards on. Players are asked to turn the card on top of their pack. Cards belong to two classes: “good” cards (i.e., the four aces, the four twos, an d the four threes), and "bad" cards (i.e., the rest).

As soon as a player, say Neal, turns a good card, say a g, the game enters a second situation in which only Jack reduces his pack: in fact, Jack needs to turn up to g of his cards in search of a good one, if he succeeds the roles swap and it is Neal who needs to exit this dangerous condition. If Jack fails to turn up a good card within g attempts, all cards stacked on the table go on the bottom of Neal's pack. Whoever wins the cards, the first situation starts again. If a player exhausts their pack in search of a good card, the game is over and the opponent wins.

Three "main" functions are available: one uses a single game simulation process, one uses fork() to launch several processes, and another one uses a LINDA approach to execute in parallel a number of processes via eval().

More information on the game is available at http://www.snotskie.com/the-good-the-bad-and-chaos-in-childrens-card-games/

A paper describing HeartQuake as a dynamic system is "The HeartQuake Dynamic System", Complex Systems 9(2), ISSN 0891-2513, available at http://www.complex-systems.com/abstracts/v09_i02_a01/
