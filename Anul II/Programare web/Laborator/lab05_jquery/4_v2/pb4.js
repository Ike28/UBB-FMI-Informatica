document.addEventListener("DOMContentLoaded", function () {
    const table = $('#fruits');
    const headers = $(table).find('th');
    const tableBody = $(table).find('tbody');
    const rows = $(table).find('tr');

    const directions = Array.from(headers).map(function (header) {
        return '';
    });

    function transform(index, content) {
        const type = $(headers[index]).data('type');
        switch (type) {
            case "number":
                return parseInt(content);
            case "string":
                return content;
            default:
                return content;
        }
    }

    function sortColumn(index) {
        const newRows = Array.from(rows);

        const direction = directions[index] || 'asc';
        let multiplier;
        if (direction === 'asc') {
            multiplier = 1;
        } else multiplier = -1;

        newRows.sort(function (rowA, rowB) {
            const cellA = $(rowA).find('td').eq(index).html();
            const cellB = $(rowB).find('td').eq(index).html();

            const a = transform(index, cellA);
            const b = transform(index, cellB);

            switch (true) {
                case a > b:
                    return multiplier;
                case a < b:
                    return -1 * multiplier;
                case a === b:
                    return 0;
            }
        });

        rows.detach();

        // reversing the direction
        if (direction === 'asc') {
            directions[index] = 'desc';
        } else {
            directions[index] = 'asc';
        }

        newRows.forEach(function (newRow) {
            tableBody.append(newRow);
        })
    }

    headers.each(function (index) {
        $(this).on('click', function () {
            sortColumn(index);
        });
    });
});
