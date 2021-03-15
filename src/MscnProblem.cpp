#include "../include/MscnProblem.h"

MscnProblem::MscnProblem() {
    sd_tab = new Table<double>(0);
    sf_tab = new Table<double>(0);
    sm_tab = new Table<double>(0);
    ss_tab = new Table<double>(0);

    cd_mat = new Matrix<double>(0,0);
    cf_mat = new Matrix<double>(0,0);
    cm_mat = new Matrix<double>(0,0);

    ud_tab = new Table<double>(0);
    uf_tab = new Table<double>(0);
    um_tab = new Table<double>(0);

    ps_income_tab = new Table<double>(0);

    xd = new Matrix<double>(0,0);
    xf = new Matrix<double>(0,0);
    xm = new Matrix<double>(0,0);

    xd_min = new Matrix<double>(0, 0);
    xd_max = new Matrix<double>(0, 0);
    xf_min = new Matrix<double>(0, 0);
    xf_max = new Matrix<double>(0, 0);
    xm_min = new Matrix<double>(0, 0);
    xm_max = new Matrix<double>(0, 0);

    solution = new Table<double>(0);
    d_count = 0;
    f_count = 0;
    m_count = 0;
    s_count = 0;
}

MscnProblem::~MscnProblem() {
    delete sd_tab;
    delete sf_tab;
    delete sm_tab;
    delete ss_tab;

    delete cd_mat;
    delete cf_mat;
    delete cm_mat;

    delete ud_tab;
    delete uf_tab;
    delete um_tab;
    delete ps_income_tab;

    delete xd;
    delete xf;
    delete xm;

    delete xd_min;
    delete xd_max;
    delete xf_min;
    delete xf_max;
    delete xm_min;
    delete xm_max;
}

bool MscnProblem::setD_count(int new_count) {
    if (new_count <= 0)
        return false;
    d_count = new_count;

    sd_tab->setSize(d_count);
    ud_tab->setSize(d_count);
    cd_mat->setSize(d_count, f_count);

    xd->setSize(d_count, f_count);

    xd_max->setSize(d_count, f_count);
    xd_min->setSize(d_count, f_count);

    solution->setSize((d_count*f_count) + (f_count*m_count) + (m_count*s_count));

    return true;
}

bool MscnProblem::setF_count(int new_count) {
    if (new_count <= 0)
        return false;

    f_count = new_count;

    sf_tab->setSize(f_count);
    uf_tab->setSize(f_count);
    cf_mat->setSize(f_count, m_count);
    cd_mat->setSize(d_count, f_count);

    xd->setSize(d_count, f_count);
    xf->setSize(f_count, m_count);

    xd_max->setSize(d_count, f_count);
    xd_min->setSize(d_count, f_count);

    xf_max->setSize(f_count, m_count);
    xf_min->setSize(f_count, m_count);

    solution->setSize((d_count*f_count) + (f_count*m_count) + (m_count*s_count));

    return true;
}

bool MscnProblem::setM_count(int new_count) {
    if (new_count <= 0) return false;

    m_count = new_count;

    sm_tab->setSize(m_count);
    um_tab->setSize(m_count);
    cm_mat->setSize(m_count, s_count);
    cf_mat->setSize(f_count, m_count);

    xf->setSize(f_count, m_count);
    xm->setSize(m_count, s_count);

    xf_max->setSize(f_count, m_count);
    xf_min->setSize(f_count, m_count);

    xm_max->setSize(m_count, s_count);
    xm_min->setSize(m_count, s_count);

    solution->setSize((d_count*f_count) + (f_count*m_count) + (m_count*s_count));

    return true;
}

bool MscnProblem::setS_count(int new_count) {
    if (new_count <= 0) return false;
    s_count = new_count;

    ss_tab->setSize(s_count);
    ps_income_tab->setSize(s_count);
    cm_mat->setSize(m_count, s_count);

    xm->setSize(m_count, s_count);

    xm_max->setSize(m_count, s_count);
    xm_min->setSize(m_count, s_count);

    solution->setSize((d_count*f_count) + (f_count*m_count) + (m_count*s_count));

    return true;
}

bool MscnProblem::open(const char* file_name) {
    ProblemFileReader<double> freader(file_name);

    if (!setD_count(freader.loadCount()))
        return false;
    if (!setF_count(freader.loadCount()))
        return false;
    if (!setM_count(freader.loadCount()))
        return false;
    if (!setS_count(freader.loadCount()))
        return false;
    if (!freader.fillTable(sd_tab))
        return false;
    if (!freader.fillTable(sf_tab))
        return false;
    if (!freader.fillTable(sm_tab))
        return false;
    if (!freader.fillTable(ss_tab))
        return false;
    if (!freader.fillMatrix(cd_mat))
        return false;
    if (!freader.fillMatrix(cf_mat))
        return false;
    if (!freader.fillMatrix(cm_mat))
        return false;
    if (!freader.fillTable(ud_tab))
        return false;
    if (!freader.fillTable(uf_tab))
        return false;
    if (!freader.fillTable(um_tab))
        return false;
    if (!freader.fillTable(ps_income_tab))
        return false;
    if (!freader.fillBoundaryMatrix(xd_min, xd_max))
        return false;
    if (!freader.fillBoundaryMatrix(xf_min, xf_max))
        return false;
    if (!freader.fillBoundaryMatrix(xm_min, xm_max))
        return false;

    return true;
}

bool MscnProblem::save(const char* file_name) {
    ProblemFileWriter<double> fw(file_name);

    fw.printCount("D", d_count);
    fw.printCount("F", f_count);
    fw.printCount("M", m_count);
    fw.printCount("S", s_count);

    fw.printTable("sd", sd_tab);
    fw.printTable("sf", sf_tab);
    fw.printTable("sm", sm_tab);
    fw.printTable("ss", ss_tab);

    fw.printMatrix("cd", cd_mat);
    fw.printMatrix("cf", cf_mat);
    fw.printMatrix("cm", cm_mat);

    fw.printTable("ud", ud_tab);
    fw.printTable("uf", uf_tab);
    fw.printTable("um", um_tab);
    fw.printTable("ps", ps_income_tab);

    fw.printBoundaryMatrix("xdminmax", xd_min, xd_max);
    fw.printBoundaryMatrix("xfminmax", xf_min, xf_max);
    fw.printBoundaryMatrix("xmminmax", xm_min, xm_max);

    return true;
}

bool MscnProblem::saveSolution(const char* file_name) {
    ProblemFileWriter<double> pw(file_name);

    pw.printCount("D", d_count);
    pw.printCount("F", f_count);
    pw.printCount("M", m_count);
    pw.printCount("S", s_count);

    pw.printMatrix("xd", xd);
    pw.printMatrix("xf", xf);
    pw.printMatrix("xm", xm);

    return true;
}

void MscnProblem::print() {
    std::cout << d_count << std::endl;
    std::cout << f_count << std::endl;
    std::cout << m_count << std::endl;
    std::cout << s_count << std::endl;

    sd_tab->print();
    sf_tab->print();
    sm_tab->print();
    ss_tab->print();
    std::cout << std::endl;

    cd_mat->print();
    cf_mat->print();
    cm_mat->print();
    std::cout << std::endl;

    ud_tab->print();
    uf_tab->print();
    um_tab->print();
    ps_income_tab->print();
    std::cout << std::endl;

    xd->print();
    xf->print();
    xm->print();

    xd_min->print();
    xd_max->print();
    xf_min->print();
    xf_max->print();
    xm_min->print();
    xm_max->print();
}

bool MscnProblem::initSolution(Table<double>* solution) {

    for (int i = 0; i < f_count; i++) {
        for (int j = 0; j < d_count; j++)
            xd->set(j, i, solution->get(i * d_count + j));
    }

    int xd_size = d_count * f_count;
    for (int i = 0; i < m_count; i++){
        for (int j = 0; j < f_count; j++)
            xf->set(j,i,solution->get(xd_size + i * f_count + j));
    }

    int xf_size = xd_size + f_count * m_count;
    for (int i = 0; i < s_count; i++) {
        for (int j = 0; j < m_count; j++)
            xm->set(j,i,solution->get(xf_size + i * m_count + j));
    }

    return true;
}

void MscnProblem::qualitySatisfier() {
    for (int i = 0; i < f_count; i++) {
        for (int j = 0; j < d_count; j++) {
            if (xd->get(i, j) < xd_min->get(i, j))
                xd->set(i, j,0);
            if (xd->get(i, j) > xd_max->get(i, j))
                xd->set(i, j, X_MAX);
        }
    }

    for (int i = 0; i < m_count; i++) {
        for (int j = 0; j < f_count; j++) {
            if (xf->get(i, j) < xf_min->get(i, j))
                xf->set(i, j,0);
            if (xf->get(i, j) > xf_max->get(i, j))
                xf->set(i, j, X_MAX);
        }
    }

    for (int i = 0; i < s_count; i++) {
        for (int j = 0; j < m_count; j++) {
            if (xm->get(i, j) < xm_min->get(i, j))
                xm->set(i, j,0);
            if (xm->get(i, j) > xm_max->get(i, j))
                xm->set(i, j, X_MAX);
        }
    }
}

double MscnProblem::getQuality() {
    double difference = 0;

    //producting power/s/check
    for (int i = 0; i < d_count; i++) {
        difference += (sd_tab->get(i) - xd->sumColumn(i));
        if (difference < 0) {
            difference *= -1.02;
            difference /= d_count;
            for (int j = 0; j < xd->get_rows_amount(); j++)
                xd->set(i, j, xd->get(i, j) - difference);
        }
    }

    for (int i = 0; i < f_count; i++) {
        difference = sf_tab->get(i) - xf->sumColumn(i);
        if (difference < 0) {
            difference *= -1.02;
            difference /= f_count*xf->get_rows_amount();
            for (int j = 0; j < xf->get_rows_amount(); j++)
                xf->set(i, j, xf->get(i, j) - difference);
        }
    }

    for (int i = 0; i < m_count; i++) {
        difference = sm_tab->get(i) - xm->sumColumn(i);
        if (difference < 0) {
            difference *= -1.02;
            difference /= m_count;
            for (int j = 0; j < xm->get_rows_amount(); j++)
                xm->set(i, j, xm->get(i, j) - difference);
        }
    }

    for (int i = 0; i < m_count; i++) {
        difference = ss_tab->get(i) - xm->sumColumn(i);
        if (difference < 0) {
            difference *= -1.02;
            difference /= m_count;
            for (int i = 0; i < m_count; i++) {
                for (int j = 0; j < xm->get_rows_amount(); j++)
                    xm->set(i, j, xm->get(i, j) - difference);
            }
        }
    }

    //outcome>income?
    difference = 0;
    for (int i = 0; i < f_count; i++) {
        difference +=  xd->sumRow(i) - xf->sumColumn(i);
        if (difference < 0) {
            difference *= -1.02;
            difference /= f_count;
            for (int j = 0; j < xf->get_rows_amount(); j++)
                xf->set(i, j, xf->get(i, j) - difference);
            }
    }
    difference = 0;

    for (int i = 0; i < m_count; i++) {
        difference +=  xf->sumRow(i) - xm->sumColumn(i);
        if (difference < 0) {
            difference *= -1.02;
            difference /= m_count;
            for (int j = 0; j < xm->get_rows_amount(); j++)
                xm->set(i, j, xm->get(i, j) - difference);
        }
    }
    qualitySatisfier();

    double kt = 0;

    for (int i = 0; i < f_count; i++) {
        for (int j = 0; j < d_count; j++)
            kt += cd_mat->get(i, j) * xd->get(i, j);
    }

    for (int i = 0; i < m_count; i++) {
        for (int j = 0; j < f_count; j++) {
            kt += cf_mat->get(i, j) * xf->get(i, j);
        }
    }

    for (int i = 0; i < s_count; i++) {
        for (int j = 0; j < m_count; j++) {
            kt += cm_mat->get(i, j) * xm->get(i, j);
        }
    }

    double ku = 0;

    for (int i = 0; i < d_count; i ++) {
        ku += xd->filledSpotsInCol(i) * ud_tab->get(i);
    }

    for (int i = 0; i < f_count; i++) {
        ku += xf->filledSpotsInCol(i) * uf_tab->get(i);
    }

    for (int i = 0; i < m_count; i++) {
        ku += xm->filledSpotsInCol(i) * um_tab->get(i);
    }

    double ps = 0;

    for (int i = 0; i < s_count; i++){
        for (int j = 0; j < m_count; j++) {
            ps += ps_income_tab->get(i) * xm->get(i, j);
        }
    }

    return ps - (kt + ku);
}

void MscnProblem::generateInstance(Random *ra) {
    setD_count(ra->randomInteger(1, MAX_COUNT));
    setF_count(ra->randomInteger(1, MAX_COUNT));
    setM_count(ra->randomInteger(1, MAX_COUNT));
    setS_count(ra->randomInteger(1, MAX_COUNT));

    ra->fillMatrix(cd_mat, 1, C_MAX);
    ra->fillMatrix(cf_mat, 1, C_MAX);
    ra->fillMatrix(cm_mat, 1, C_MAX);

    ra->randFillTable(ud_tab, 1, U_MAX);
    ra->randFillTable(uf_tab, 1, U_MAX);
    ra->randFillTable(um_tab, 1, U_MAX);
    ra->randFillTable(ps_income_tab, 1, INCOME_MAX);

    ra->randFillTable(sd_tab, 1, S_MAX);
    ra->randFillTable(sf_tab, 1, S_MAX);
    ra->randFillTable(sm_tab, 1, S_MAX);
    ra->randFillTable(ss_tab, 1, S_MAX);

    xd_min->fillMatrixWith(0);
    xd_max->fillMatrixWith(X_MAX);
    xf_min->fillMatrixWith(0);
    xf_max->fillMatrixWith(X_MAX);
    xm_min->fillMatrixWith(0);
    xm_max->fillMatrixWith(X_MAX);
}

Table<double>* MscnProblem::getSolution() {
    return solution;
}

void MscnProblem::setSolution(Table<double>* table) {
    solution->setSize(table->getSize());

    for (int i = 0; i < solution->getSize(); i++) {
        solution->set(i, table->get(i));
    }
}
