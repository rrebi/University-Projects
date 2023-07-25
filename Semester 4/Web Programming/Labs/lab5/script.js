var allDivs = document.querySelectorAll(".container *")
var dragged = undefined;


allDivs.forEach(function (element){
    element.dragged = true;

    element.addEventListener("dragstart", function(event)
    {
        // store a reference on the dragged element
        dragged = event.target;
    });

    element.addEventListener("dragover", function(event){
        event.preventDefault();
    });
 
    element.addEventListener("drop", function(event){
        if(event.target.className == "dropZone"){
            event.target.appendChild(dragged);
        }

        if(event.target.className == "dragZone"){
            event.target.appendChild(dragged);
        }
    });
});
