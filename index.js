
const burger = document.querySelector('.burger');
const nav = document.querySelector('.nav-links');

burger.addEventListener('click', () => {
    nav.classList.toggle('active');
    burger.classList.toggle('active');
});


const scrollTopBtn = document.getElementById('scrollTopBtn');

window.onscroll = () => {
    if (document.body.scrollTop > 200 || document.documentElement.scrollTop > 200) {
        scrollTopBtn.style.display = 'block';
    } else {
        scrollTopBtn.style.display = 'none';
    }
};

scrollTopBtn.addEventListener('click', () => {
    window.scrollTo({top: 0, behavior: 'smooth'});
});

// Intersection Observer pour animation au scroll
const observerOptions = {
    threshold: 0.1,
    rootMargin: '0px 0px -50px 0px'
};

const observer = new IntersectionObserver((entries) => {
    entries.forEach(entry => {
        if (entry.isIntersecting) {
            entry.target.classList.add('animate-in');
            // optionnel : observer.unobserve(entry.target);
        }
    });
}, observerOptions);

// Observer les sections
document.querySelectorAll('section').forEach(section => {
    section.classList.add('fade-section');
    observer.observe(section);
});

// Observer les cartes de projets
document.querySelectorAll('.project-card').forEach((card, index) => {
    card.classList.add('fade-card');
    card.style.animationDelay = `${index * 0.1}s`;
    observer.observe(card);
});

// Observer les éléments de liste (compétences, contact)
document.querySelectorAll('#about ul li').forEach((item, index) => {
    item.classList.add('fade-item');
    item.style.animationDelay = `${index * 0.08}s`;
    observer.observe(item);
});

// Observer les items de contact
document.querySelectorAll('.contact-list li').forEach((item, index) => {
    item.style.animationDelay = `${index * 0.12}s`;
    observer.observe(item);
});