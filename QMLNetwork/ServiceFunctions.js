// Adding pages to SwipeView and deleting them

function addScreen()
{
    var page = screenComponent.createObject(swipe);
    swipe.addItem(page);
    swipe.currentIndex = swipe.count - 1;
}

function removeScreen()
{
    swipe.removeItem(swipe.currentItem);
}
