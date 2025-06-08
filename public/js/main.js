const sliderData = [
    {
        id: 0,
        "active": "active",
        "imgSrc":"./public/img/img/slide/01landinggear.jpg",
        "alt":"Aircraft landing gear experiment",
        "h5Text":"Aircraft Landing Gears",
        "alink":"https://www.mdpi.com/2076-3417/10/4/1459",
        "pText":"Aircraft landing gear equipped with a magnetorheological (MR) damper is a semi-active system that contains nonlinear behavior, disturbances, uncertainties, and delay times."
    },
    {
        id: 1,
        "active": "",
        "imgSrc":"./public/img/img/slide/02tunnalcar381x400.jpg",
        "alt":"Diagram of the tunnel car",
        "h5Text":"Tunnel Car",
        "alink":"",
        "pText":"The Tunnel car can discover the objects in the tunnel"
    },
    {
        id: 2,
        "active": "",
        "imgSrc":"./public/img/img/slide/03exe545x409.jpg",
        "alt":"Diagram of the ",
        "h5Text":"Tunnel Car",
        "alink":"https://github.com/vietluongquoc/manipulator-iot",
        "pText":"The Tunnel car can discover the objects in the tunnel"
    },

];



const sliderFun = ()=>{
    $('#carousel-indicators').empty();$('#carousel-inner').empty();
    sliderData.forEach((slide)=>{
        $(`<li data-target="#carouseSlider" data-slide-to="${slide.id}" class="${slide.active}"></li>`).appendTo($('#carousel-indicators'));
        $(`<div class="item"> 
                <img src="${slide.imgSrc}" alt="Third slide">
                <h5 class="slidertext"><a href="${slide.alink}">${slide.h5Text}</a></h5>
                <p class="slidertext">${slide.pText} </p>
            </div>">`).appendTo($('#carousel-inner'));
    });
};

const convertTojson = ()=>{
    $('form').submit(()=>{
        formData.push($('form').value());
    })
}

$(document).ready(()=>{
    // sliderFun();
});