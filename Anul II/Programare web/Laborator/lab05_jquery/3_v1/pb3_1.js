const boxes = $('.box').toArray();

let first;
let second;
let matchCounter = 0;

boxes.forEach(function (box) {
    const order = Math.floor(Math.random() * 16).toString();
    $(box).css('order', order);
    $(box).on('click', function () {
        if (!first && !second) {
            first = box;
            $(box).addClass('show')
        } else if (first && !second) {
            second = box;
            $(box).addClass('show');
            if ($(first).html() === $(second).html()) {
                $(first).css('pointer-events', 'none');
                $(second).css('pointer-events', 'none');
                first = null;
                second = null;
                matchCounter++;
                if (matchCounter >= 8) setTimeout(() => window.alert("Congrats, you won! Refresh the page to keep playing!"), 1000);
            } else {
                $(first).addClass('hide');
                $(second).addClass('hide');
                setTimeout(() => {
                    $(first).removeClass('show hide');
                    $(second).removeClass('show hide');
                    first = null;
                    second = null;
                }, 2000);
            }
        }
    })
});