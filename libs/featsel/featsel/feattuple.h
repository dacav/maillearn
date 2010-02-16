/*
 * Copyright 2010 Giovanni Simoni
 *
 * This file is part of maillearn.
 *
 * maillearn is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * maillearn is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with maillearn.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef __defined_featsel_feattuple_h
#define __defined_featsel_feattuple_h

feat_tuple_t *featsel_analyze (featsel_t *fs, void *elem);

void featsel_tuple_free (feat_tuple_t *t);

double featsel_tuple_distance (feat_tuple_t *t0, feat_tuple_t *t1);

#endif // __defined_featsel_feattuple_h