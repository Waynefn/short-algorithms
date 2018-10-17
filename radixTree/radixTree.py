class Node:
    def __init__(self, link, prefix=""):
        self.prefix = prefix
        self.link = link
        self.next=[None,None]

    def set_node(self, next0, next1):
        self.next[0] = next0
        self.next[1] = next1

    def __len__(self):
        return len(self.prefix)

    def __repr__(self):
        if self.link:
            return f"{self.prefix}[{len(self)}] -> {self.link}"
        return f"{self.prefix}[{len(self)}] -> D"


class RadixTree:
    def __init__(self, default_link):
        self.root = None
        self.default_link = default_link

    def ip2bin(ip):
        return "{0[0]:08b}{0[1]:08b}{0[2]:08b}{0[3]:08b}".format(list(map(int, ip.split('.'))))

    def common_prefix(a, b):
        if a == b:
            return a
        if len(a) > len(b):
            a, b = b, a
        for i in range(len(a)):
            if a[i] != b[i]:
                return a[:i]
        return a

    def find_link(self, ip):
        if '.' in ip:
            pf=RadixTree.ip2bin(ip)
        else:
            pf=ip.replace(' ', '')
        return self._find_link(self.root, pf, None)

    def _find_link(self, p, pf, link):
        if not p:
            return link
        cpf = RadixTree.common_prefix(p.prefix, pf)
        if cpf!=p.prefix:
            return link or self.default_link
        else:
            link=p.link

        left=pf[len(cpf):]
        return self._find_link(p.next[int(left[0])],left,link) or self.default_link


    def insert(self, prefix, link):
        pf = prefix.replace(' ', '')
        self.root = self._insert(self.root, pf, link)

    def print_tree(self):
        self._print_tree(self.root, 0)

    def _print_tree(self, p, level):
        if not p: return
        print('  ' * level, p)
        self._print_tree(p.next[0], level + 1)
        self._print_tree(p.next[1], level + 1)

    def _insert(self, p, pf, link):
        if not p:
            q = Node(link, pf)
            return q
        elif pf==p.prefix:
            p.link=link
        else:
            cpf = RadixTree.common_prefix(p.prefix, pf)
            if p.prefix == cpf:
                pf=pf[len(cpf):]
                n=int(pf[0])
                p.next[n]=self._insert(p.next[n],pf,link)
            elif pf == cpf:
                pf=p.prefix[len(pf):]
                n = int(pf[0])
                p.next[n] = self._insert(p.next[n], pf, p.link)
                p.prefix=cpf
                p.link=link
            else:
                a = p.prefix[len(cpf):]
                n=int(a[0])
                q=Node(p.link,a)
                q.next=p.next[:]
                p.prefix=cpf
                p.link=None
                p.next[n] = q
                p.next[1-n]=None
                b = pf[len(cpf):]
                n = int(b[0])
                p.next[n] = self._insert(p.next[n], b, link)
        return p


a = '11001000 00010111 0001 0'
b = '11001000 00010111 0001 1000'
c = '11001000 00010111 0001 1'
r = RadixTree(5)
r.insert(a,1)
r.insert(b,2)
r.insert(c,3)
r.print_tree()

f1=r.find_link("11001000 00011110 10100000 00001011")
f2=r.find_link("11001000 00010111 00011000 00011110")
f3=r.find_link("11001000 00010111 00011111 00100010")
print(f1,f2,f3)
