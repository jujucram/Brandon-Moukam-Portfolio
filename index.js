
const burger = document.querySelector('.burger');
const nav = document.querySelector('.nav-links');

if (burger) {
    burger.addEventListener('click', () => {
        const opened = nav.classList.toggle('active');
        burger.classList.toggle('active');
        // update aria-expanded for accessibility
        burger.setAttribute('aria-expanded', opened ? 'true' : 'false');
    });
}


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

const observerOptions = {
    threshold: 0.1,
    rootMargin: '0px 0px -50px 0px'
};

const observer = new IntersectionObserver((entries) => {
    entries.forEach(entry => {
        if (entry.isIntersecting) {
            entry.target.classList.add('animate-in');
            
        }
    });
}, observerOptions);


document.querySelectorAll('section').forEach(section => {
    section.classList.add('fade-section');
    observer.observe(section);
});


document.querySelectorAll('.project-card').forEach((card, index) => {
    card.classList.add('fade-card');
    card.style.animationDelay = `${index * 0.1}s`;
    observer.observe(card);
});
document.querySelectorAll('#about ul li').forEach((item, index) => {
    item.classList.add('fade-item');
    item.style.animationDelay = `${index * 0.08}s`;
    observer.observe(item);
});


document.querySelectorAll('.contact-list li').forEach((item, index) => {
    item.style.animationDelay = `${index * 0.12}s`;
    observer.observe(item);
});


const openCertBtn = document.getElementById('openCertBtn');
const certModal = document.getElementById('certModal');
const modalClose = document.querySelector('.modal-close');

function openCert() {
    if (!certModal) return;
    certModal.setAttribute('aria-hidden', 'false');
    document.body.style.overflow = 'hidden';
}

function closeCert() {
    if (!certModal) return;
    certModal.setAttribute('aria-hidden', 'true');
    document.body.style.overflow = '';
}

if (openCertBtn) openCertBtn.addEventListener('click', openCert);
if (modalClose) modalClose.addEventListener('click', closeCert);


if (certModal) {
    certModal.addEventListener('click', (e) => {
        if (e.target === certModal) closeCert();
    });
}


document.addEventListener('keydown', (e) => {
    if (e.key === 'Escape') closeCert();
});

// Fallback handling for iframe PDF display
const certIframe = document.querySelector('#certModal iframe');
const certFallback = document.getElementById('certFallback');
const certOpenNew = document.getElementById('certOpenNew');

function showFallback() {
    if (certFallback) certFallback.style.display = 'block';
}

function hideFallback() {
    if (certFallback) certFallback.style.display = 'none';
}

if (certIframe) {
    // hide fallback initially
    hideFallback();
    // If iframe loads, hide fallback
    certIframe.addEventListener('load', () => {
        // small delay to ensure content painted
        setTimeout(() => { hideFallback(); }, 200);
    });
}

// When opening the modal, try to detect if iframe will likely work. If not, show fallback link.
function openCert() {
    if (!certModal) return;
    certModal.setAttribute('aria-hidden', 'false');
    document.body.style.overflow = 'hidden';

    // ensure iframe src is set
    if (certIframe && !certIframe.getAttribute('src')) {
        certIframe.setAttribute('src', 'Certificat_Developpeur_Web_FINAL_Brandon.pdf');
    }

    // after a short delay, if iframe still empty or not loaded, show fallback
    setTimeout(() => {
        // For local file:// or blocked inline PDF, iframe may not load — show fallback
        // We cannot reliably detect cross-origin errors; use presence of contentWindow.document body as heuristic
        try {
            const doc = certIframe && certIframe.contentDocument;
            const hasContent = doc && doc.body && doc.body.childNodes.length > 0;
            if (!hasContent) showFallback(); else hideFallback();
        } catch (err) {
            // accessing contentDocument may throw — show fallback
            showFallback();
        }
    }, 700);
}

// Ensure fallback link points to the PDF file
if (certOpenNew) certOpenNew.setAttribute('href', 'Certificat_Developpeur_Web_FINAL_Brandon.pdf');

// Top header button scroll to top
const topHeaderBtn = document.getElementById('topHeaderBtn');
if (topHeaderBtn) {
    topHeaderBtn.addEventListener('click', () => {
        window.scrollTo({ top: 0, behavior: 'smooth' });
    });
}