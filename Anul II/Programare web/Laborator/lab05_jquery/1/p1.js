$("#list1").dblclick(function () {
    return $("#list1 option:selected").remove().appendTo("#list2");
});
$("#list2").dblclick(function () {
    return $("#list2 option:selected").remove().appendTo("#list1");
});