<?php
    header("Access-Control-Allow-Origin: *");
    $game = explode(",", $_GET["game"]);
    $gameFinished = true;

    foreach ($game as $g) {
        if ($g == "/") {
            $gameFinished = false;
            break;
        }
    }

    // Daca nu s-a terminat jocul, face Computer o mutare.
    $computerPos;
    if (!$gameFinished) {
        $computerPos = rand(0, 8);
        while ($game[$computerPos] != "/") {
            $computerPos = rand(0, 8);
        }
        $game[$computerPos] = "0";
    }

    $winner = "none";
    if ($game[0] == 'X' and $game[1] == 'X' and $game[2] == 'X')
        $winner = "player";

    if ($game[3] == 'X' and $game[4] == 'X' and $game[5] == 'X')
        $winner = "player";

    if ($game[1] == 'X' and $game[4] == 'X' and $game[7] == 'X')
        $winner = "player";

    if ($game[0] == 'X' and $game[3] == 'X' and $game[6] == 'X')
        $winner = "player";

    if ($game[2] == 'X' and $game[5] == 'X' and $game[8] == 'X')
        $winner = "player";

    if ($game[6] == 'X' and $game[7] == 'X' and $game[8] == 'X')
        $winner = "player";

    if ($game[0] == 'X' and $game[4] == 'X' and $game[8] == 'X')
        $winner = "player";

    if ($game[2] == 'X' and $game[4] == 'X' and $game[6] == 'X')
        $winner = "player";

    if ($game[0] == '0' and $game[1] == '0' and $game[2] == '0')
        $winner = "computer";

    if ($game[0] == '0' and $game[3] == '0' and $game[6] == '0')
        $winner = "computer";

    if ($game[2] == '0' and $game[5] == '0' and $game[8] == '0')
        $winner = "computer";

    if ($game[6] == '0' and $game[7] == '0' and $game[8] == '0')
        $winner = "computer";

    if ($game[0] == '0' and $game[4] == '0' and $game[8] == '0')
        $winner = "computer";

    if ($game[2] == '0' and $game[4] == '0' and $game[6] == '0')
        $winner = "computer";

    if ($game[3] == '0' and $game[4] == '0' and $game[5] == '0')
        $winner = "computer";

    if ($game[1] == '0' and $game[4] == '0' and $game[7] == '0')
        $winner = "computer";

    if ($winner == "none") {
        $gameFinished = true;
        foreach ($game as $g) {
            if ($g == "/") {
                $gameFinished = false;
                break;
            }
        }

        if ($gameFinished) {
            echo "draw";
        } else {
            echo $computerPos;
        }
    } else if ($winner == "computer") {
        echo "computerwin";
    } else {
        echo "humanwin";
    }
?>
