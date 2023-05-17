const cards = $('.card').toArray();

let flippedCard = false;
let first, second;
let lockBoard = false; //locking the board so only 2 cards can be flipped at once
let matchCounter = 0;
let clickCounter = 0;

function flipCard() {
    //clickCounter++;
    if (lockBoard) return;
    if (this === first) return; //checks to see if the player clicked on the same card twice

    $(this).addClass('flip');
    if (!flippedCard) {
        flippedCard = true;
        first = this;
        return;
    }
    second = this;
    checkForMatch();
}

function checkForMatch() {
    clickCounter += 2;
    if ($(first).data('prof') === $(second).data('prof')) {
        //disabling the cards, so we can't click on them again
        $(first).off('click', flipCard);
        $(second).off('click', flipCard);
        matchCounter++;
        [flippedCard, lockBoard] = [false, false];
        [first, second] = [null, null];
        if (matchCounter >= 6) {
            setTimeout(() => window.alert("Congrats, you won! Refresh the page to keep playing!"), 1000);
            $('#won').html("Congrats! You won in: " + clickCounter.toString() + " clicks");
        }
        return;
    }
    lockBoard = true;
    //unflipping the cards if the match is incorrect
    setTimeout(() => {
        $(first).removeClass('flip');
        $(second).removeClass('flip');
        resetBoard();
    }, 1000);
}

function resetBoard() {
    [flippedCard, lockBoard] = [false, false];
    [first, second] = [null, null];
}

(function shuffle() {
    $('.card').each(function () {
        $(this).css('order', Math.floor(Math.random() * 12).toString());
    });
})();

$(cards).on('click', flipCard);