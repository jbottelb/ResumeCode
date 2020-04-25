function [value, move] = AIminimax (gameBoard, depth, alpha, beta, currentPlayer, maximizingPlayer)
%% THE MIN MAX AI 
% This AI Impliments Minimax

% Created by Josh Bottelberghe
% Last edit 4/20/19

value = 0; % should be replaced
move = 2; % should NEVER be used
isTerminal = false;
 % column the AI moves to
if currentPlayer == 1
    oppPlayer = 2;
else
    oppPlayer = 1;
end
if maximizingPlayer == 1
    humPlayer = 2;
else
    humPlayer = 1;
end
% designate opposing player for in general
% designate human player role to AI
% AI = current Player

%% Catch terminal node
if checkWin2(gameBoard, maximizingPlayer) ~= 0 || checkWin2(gameBoard, humPlayer) ~= 0
    if checkWin2(gameBoard, maximizingPlayer) == maximizingPlayer
        value = 100000000;
    elseif checkWin2(gameBoard, humPlayer) == humPlayer
        value = -100000000;
    else
        value = 0;
    end
    isTerminal = true;
elseif depth == 0
    value = score(gameBoard, maximizingPlayer);
    isTerminal = true;
end % end catch terminal node

%% Maximising player
if currentPlayer == maximizingPlayer && ~isTerminal
    value = - inf;
    for xi = 1:1:7
        testBoard = placePiece(maximizingPlayer, xi, gameBoard);
        [newScore, ~] = AIminimax(testBoard, depth - 1, alpha, beta, oppPlayer, maximizingPlayer);
        if gameBoard(1, xi) ~= 0
            newScore = - inf;
        end % catch cant play there
        if newScore > value
            value = newScore;
            move = xi;
        end
        alpha = max(value, alpha);
        if alpha >= beta
            break;
        end
    end
end
%% Minimizing player
if currentPlayer ~= maximizingPlayer && ~isTerminal
    value = inf;
    for xi = 1:1:7
        testBoard = placePiece(currentPlayer, xi, gameBoard);
        [newScore, ~] = AIminimax(testBoard, depth - 1, alpha, beta, oppPlayer, maximizingPlayer);
        if gameBoard(1, xi) ~= 0
            newScore = inf;
        end % catch cant play there
        if newScore < value
            value = newScore;
            move = xi;
        end
        beta = min(value, beta);
        if alpha >= beta
            break;
        end
    end
end
end
